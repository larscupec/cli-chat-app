#include "Server.hpp"
#include "Chat.hpp"
#include "Debug.hpp"
#include "JsonFileWriter.hpp"
#include "Message.hpp"
#include "ServerChatHandler.hpp"
#include "ServerConnectionHandler.hpp"
#include "enet/enet.h"
#include <stdexcept>
#include <string>

const size_t MAX_USER_COUNT = 32;
const size_t MAX_CHANNELS = 2;
const unsigned int INCOMING_BANDWIDTH = 0;
const unsigned int OUTGOING_BANDWIDTH = 0;
const unsigned int EVENT_TIMEOUT_MS = 1000;

Server::Server(int port) {
  address.host = ENET_HOST_ANY;
  address.port = port;

  Debug::Log("Creatng an ENet host for the server...");

  server = enet_host_create(&address, MAX_USER_COUNT, MAX_CHANNELS, INCOMING_BANDWIDTH, OUTGOING_BANDWIDTH);

  if (!server) {
    Debug::Log("An error occurred while trying to create an ENet host for the "
               "server.");
    throw std::runtime_error("An error occurred while trying to create an ENet "
                             "host for the server.");
  }

  chat = new Chat();

  ServerConnectionHandler *connectionHandler =
    new ServerConnectionHandler(this, chat);
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
    if (enet_host_service(server, &event, EVENT_TIMEOUT_MS) > 0) {
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
  Debug::Log("Saving conversation...");
  JsonFileWriter conversationFile("./conversation.json");
  conversationFile.Write(chat->ToJson());

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
