#include "ServerConnectionHandler.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "UserColorMessage.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <string>
#include <random>

ServerConnectionHandler::ServerConnectionHandler(Server *server)
    : server(server) {}

bool ServerConnectionHandler::HandleMessage(Message *message, ENetPeer *peer) {

  if (message->GetType() != MessageType::CLIENT_INFO) {
    return false;
  }

  ClientInfoMessage *clientInfo = (ClientInfoMessage*)message;

  std::random_device device;
  std::mt19937 randomNumberGenerator(device());
  std::uniform_int_distribution<std::mt19937::result_type> distribution(2, 7);

  int userColor = distribution(randomNumberGenerator);
  peer->data = new User(clientInfo->GetUsername(), userColor);

  Debug::Log("Server: " + clientInfo->GetUsername() + " has joined the server.");

  const int serverChatColor = 8;

  UserColorMessage *userColorMessage = new UserColorMessage(userColor);
  server->SendTo(peer, userColorMessage);
  
  ChatMessage welcomeMessage("Server", serverChatColor, clientInfo->GetUsername() + " has joined the server.");
  server->Broadcast(&welcomeMessage);

  return true;
}
