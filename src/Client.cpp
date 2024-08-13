#include "Client.hpp"
#include "ClientChatHandler.hpp"
#include "ClientInfoMessage.hpp"
#include "Debug.hpp"
#include <enet/enet.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <chrono>

Client::Client(std::string username) : username(username) {
  Debug::Log("Creating an ENet host for the client...");
  client = enet_host_create(NULL, 1, 2, 0, 0);

  if (!client) {
    Debug::LogError(
        "An error occurred while trying to create an ENet host for the "
        "client.");
    throw std::runtime_error("An error occurred while trying to create an ENet "
                             "host for the client.");
  }

  messageHandler = new ClientChatHandler();
}

Client::~Client() {
  Debug::Log("Closing the client...");
  enet_host_destroy(client);
}

bool Client::ConnectTo(std::string ip, int port) {
  if (isConnected) {
    Debug::LogError("Client: Already connected to a server");
    return false;
  }
  
  Debug::Log("Client: Connecting to " + ip + " on port " +
             std::to_string(port));

  ENetEvent event;
  ENetAddress address;

  enet_address_set_host(&address, ip.c_str());
  address.port = port;

  connection = enet_host_connect(client, &address, 2, 0);

  if (!connection) {
    Debug::LogError(
        "Client: No available peers for initiating an ENet connection.");
    throw std::runtime_error(
        "Client: No available peers for initiating an ENet connection.");
  }

  if (enet_host_service(client, &event, 5000) > 0 &&
      event.type == ENET_EVENT_TYPE_CONNECT) {
    Debug::Log("Client: Successfully connected to " + ip + " on port " +
               std::to_string(port));

    isConnected = true;

    Debug::Log("Client: Sending client info to the server...");
    ClientInfoMessage clientInfo(username);
    Send(&clientInfo);
    
  } else {
    enet_peer_reset(connection);
    Debug::Log("Client: Failed to connect to " + ip + " on port " +
               std::to_string(port));
  }
  
  return isConnected;
}

void Client::Listen() {
  if (!isConnected) {
    Debug::LogError("Client: Not connected to a server");
    return;
  }
  
  ENetEvent event;

  isListening = true;

  while (isListening) {
    if (enet_host_service(client, &event, 1000) > 0) {
      switch (event.type) {
      case ENET_EVENT_TYPE_RECEIVE: {
        json data = json::parse((char *)event.packet->data);
        unsigned int dataLength = event.packet->dataLength;
        Message *message = Message::Parse(data);

        Debug::Log("Client: A [" + message->GetTypeAsString() +
                   "] packet of length " + std::to_string(dataLength) +
                   " was received from the server");

        messageHandler->Handle(message, connection);

        delete message;
        enet_packet_destroy(event.packet);
        break;
      }
      }
    }
  }

  // If it stopped listening that means it wants to disconnect
  Debug::Log("Client: Disconnecting from the server...");
  enet_peer_disconnect(connection, 0);
  
  Debug::Log("Client: Waiting for disconnect acknowledgment...");
  while (enet_host_service(client, &event, 3000) > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_RECEIVE:
      Debug::Log("Client: Destroying packet");
      enet_packet_destroy(event.packet);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      Debug::Log("Client: Received disconnect acknowledgment");
      isConnected = false;
      break;
    }
  }

  // Force disconnect
  if (isConnected) {
    Debug::LogWarning("Client: Didn't receive disconnect acknowledgment, forcing connection reset");
    enet_peer_reset(connection);
    isConnected = false;
  }

  Debug::Log("Client: You left the server");
}

void Client::Send(Message *message) {
  std::string messageString = message->ToJson().dump();
  ENetPacket *packet = enet_packet_create(messageString.c_str(),
                                          strlen(messageString.c_str()) + 1,
                                          ENET_PACKET_FLAG_RELIABLE);
  enet_peer_send(connection, 0, packet);
}

void Client::Disconnect() {
  Debug::Log("Client: Stopped listening...");
  isListening = false;
}
