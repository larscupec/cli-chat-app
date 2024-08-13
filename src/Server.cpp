#include "Server.hpp"
#include "Chat.hpp"
#include "Debug.hpp"
#include "Message.hpp"
#include "ServerChatHandler.hpp"
#include "ServerConnectionHandler.hpp"
#include "User.hpp"
#include "enet/enet.h"
#include <stdexcept>
#include <string>

const size_t MAX_USER_COUNT = 32;

Server::Server(int port) {
  address.host = ENET_HOST_ANY;
  address.port = port;

  Debug::Log("Creatng an ENet host for the server...");

  server = enet_host_create(&address, MAX_USER_COUNT, 2, 0, 0);

  if (!server) {
    Debug::Log("An error occurred while trying to create an ENet host for the "
               "server.");
    throw std::runtime_error("An error occurred while trying to create an ENet "
                             "host for the server.");
  }

  chat = new Chat();

  ServerConnectionHandler *connectionHandler =
      new ServerConnectionHandler(this);
  ServerChatHandler *chatMessageHandler = new ServerChatHandler(this, chat);

  messageHandler = connectionHandler;
  messageHandler->SetNext(chatMessageHandler);
}

Server::~Server() {
  enet_host_destroy(server);
  delete messageHandler;
  delete chat;
}

void Server::Start() {
  Debug::Log("Server started on port " + std::to_string(address.port));

  isRunning = true;

  ENetEvent event;

  while (isRunning) {
    if (enet_host_service(server, &event, 1000) > 0) {
      switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT:
        Debug::Log("Server: Incoming connection from " +
                   std::to_string(event.peer->address.host));
        break;
      case ENET_EVENT_TYPE_RECEIVE: {
        json data = json::parse((char *)event.packet->data);
        unsigned int dataLength = event.packet->dataLength;
        ENetPeer *peer = event.peer;
        Message *message = Message::Parse(data);

        Debug::Log("Server: A [" + message->GetTypeAsString() +
                   "] packet of length " + std::to_string(dataLength) +
                   " was received from " + std::to_string(peer->address.host));

        messageHandler->Handle(message, peer);

        delete message;
        enet_packet_destroy(event.packet);
        break;
      }
      case ENET_EVENT_TYPE_DISCONNECT:
        Debug::Log("Server: A user has left the server.");
        break;
      }
    }
  }
}

void Server::Stop() {
  Debug::Log("Stopping server...");
  isRunning = false;
}

void Server::SendTo(ENetPeer *peer, Message *message) {
  std::string messageString = message->ToJson().dump();
  ENetPacket *packet = enet_packet_create(messageString.c_str(),
                                          strlen(messageString.c_str()) + 1,
                                          ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(peer, 0, packet);
}

void Server::Broadcast(Message *message) {
  std::string messageString = message->ToJson().dump();
  ENetPacket *packet = enet_packet_create(messageString.c_str(),
                                          strlen(messageString.c_str()) + 1,
                                          ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(server, 0, packet);
}
