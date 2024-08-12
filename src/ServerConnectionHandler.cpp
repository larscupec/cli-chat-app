#include "ServerConnectionHandler.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include <string>

ServerConnectionHandler::ServerConnectionHandler(Server *server)
    : server(server) {}

bool ServerConnectionHandler::HandleMessage(Message *message, ENetPeer *peer) {

  if (message->GetType() != MessageType::CLIENT_INFO) {
    return false;
  }

  ClientInfoMessage *clientInfo = (ClientInfoMessage*)message;

  Debug::Log("Server: " + clientInfo->GetUsername() + " has joined the server.");

  ChatMessage welcomeMessage("Server", clientInfo->GetUsername() + " has joined the server.");
  server->Broadcast(&welcomeMessage);

  return true;
}
