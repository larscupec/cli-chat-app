#include "Server.hpp"
#include "Chat.hpp"
#include "ChatMessage.hpp"
#include "Console.hpp"
#include "Debug.hpp"
#include "DisconnectMessage.hpp"
#include "JsonFileWriter.hpp"
#include "Message.hpp"
#include "ServerChatHandler.hpp"
#include "ServerCommandMode.hpp"
#include "ServerConnectionHandler.hpp"
#include "User.hpp"
#include "UserColorTable.hpp"
#include "enet/enet.h"
#include <stdexcept>
#include <string>

const size_t MAX_USER_COUNT = 32;
const size_t MAX_CHANNELS = 2;
const unsigned int INCOMING_BANDWIDTH = 0;
const unsigned int OUTGOING_BANDWIDTH = 0;
const unsigned int EVENT_TIMEOUT_MS = 1000;

Server *Server::instance = nullptr;

Server::Server() {
  chat = new Chat();
  userColorTable = new UserColorTable();

  ServerConnectionHandler *connectionHandler =
    new ServerConnectionHandler(this);
  ServerChatHandler *chatMessageHandler = new ServerChatHandler(this);

  connectionHandler->SetNext(chatMessageHandler);

  messageHandler = connectionHandler;
}

Server::~Server() { 
  delete messageHandler;
  delete chat;
}

Server *Server::GetInstance() {
  if (!instance) {
    instance = new Server();
  }
  return instance;
}

void Server::Start(int port) {
  if (isRunning) {
    Debug::LogError("Server: Already running");
    return;
  }
  
  ENetAddress address;
  
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

  Debug::Log("Done!");
  
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
      case ENET_EVENT_TYPE_DISCONNECT: {
	User *user = (User*)event.peer->data;
	Debug::Log("Server: " + user->GetUsername() + " has left the server.");
	ChatMessage *userLeftMessage = new ChatMessage("Server", SERVER_CHAT_COLOR, user->GetUsername() + " has left the server.");
	chat->Add(userLeftMessage);
	Broadcast(userLeftMessage);
	
	delete (User*)event.peer->data;
	event.peer->data = nullptr;
        break;
      }
      }
    }
  }

  enet_host_destroy(server);
  server = nullptr;

  Debug::Log("Done!");
}

void Server::Stop() {
  Debug::Log("Server: Saving conversation...");
  JsonFileWriter conversationFile("./conversation.json");
  conversationFile.Write(chat->ToJson());

  DisconnectMessage disconnectMessage("Server shut down");
  Broadcast(&disconnectMessage);
  enet_host_flush(server);
  
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
