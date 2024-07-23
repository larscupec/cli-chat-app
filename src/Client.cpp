#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include "json.hpp"
#include <bits/stdc++.h>
#include <enet/enet.h>
#include <ncurses.h>

#include "Console.hpp"
#include "ChatWindow.hpp"
#include "Client.hpp"
#include "EnetExceptions.hpp"

Client::Client(ChatWindow* chatWindow)
{ 
  if (enet_initialize()) {
    throw EnetInitException();
  }
  
  atexit(enet_deinitialize);

  client = enet_host_create(NULL, 1, 2, 0, 0);

  if (client == NULL) {
    throw EnetClientInitException();
  }
  
  this->chatWindow = chatWindow;
  loadClientInfo();
}

Client::~Client()
{
  enet_host_destroy(client);
}

void Client::tryAutoConnect()
{
  if (autoconnectIP.length() == 0 || autoconnectPort == 0) return;

  connect(autoconnectIP, autoconnectPort);
}

void Client::update() {
  ENetEvent event;

  while (isConnected) {
    while (enet_host_service(client, &event, 1000) > 0) {
      switch (event.type) {
      case ENET_EVENT_TYPE_RECEIVE: {
        nlohmann::json data = nlohmann::json::parse((char *)event.packet->data);

        if (data["type"] == "welcome") {
          chatWindow->printMsg(data["message"]);
        } else if (data["type"] == "chat") {
          chatWindow->printChat(data["username"], data["message"],
                                data["color"]);
        } else if (data["type"] == "conversation") {
          chatWindow->loadConversation(data);
        }
        break;
      }

      case ENET_EVENT_TYPE_DISCONNECT:
        isConnected = false;
        return;
      }
    }
  }
}

void Client::connect(std::string ip, int port) {
  ENetEvent event;
  ENetAddress address;

  enet_address_set_host(&address, ip.c_str());
  address.port = port;

  peer = enet_host_connect(client, &address, 2, 0);

  if (peer == NULL) {
    fprintf(stderr, "No available peers for initiating an ENet connection.\n");
    exit(EXIT_FAILURE);
  }

  /* Wait up to 5 seconds for the connection attempt to succeed. */
  if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    // Clear screen and print success message
    clear();
    refresh();
    printw("Connection to %s:%d succeeded.\n", ip.c_str(), port);

    isConnected = true;

    // Send client info to the server
    nlohmann::json info;
    info["type"] = "clientInfo";
    info["username"] = username;
    send(info.dump());
  } else {
    enet_peer_reset(peer);
    printw("Connection to %s:%d failed.\n", ip.c_str(), port);
  }
}

void Client::disconnect() {
  ENetEvent event;
  enet_peer_disconnect(peer, 0);
  /* Allow up to 3 seconds for the disconnect to succeed and drop any packets received packets. */
  while (enet_host_service(client, &event, 3000) > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_RECEIVE:
      enet_packet_destroy(event.packet);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      isConnected = false;
      return;
    }
  }

  // Force disconnect
  enet_peer_reset(peer);
  isConnected = false;
}

void Client::send(std::string message) {
  ENetPacket *packet = enet_packet_create(message.c_str(), strlen(message.c_str()) + 1,
                                          ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer, 0, packet);
}

void Client::loadClientInfo() {
  std::ifstream file("clientInfo.json");
  nlohmann::json clientInfo = nlohmann::json::parse(file);
  file.close();
  
  username = clientInfo["username"];
  autoconnectIP = clientInfo["autoconnectIP"];
  autoconnectPort = clientInfo["autoconnectPort"];
}
