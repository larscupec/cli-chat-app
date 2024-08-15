#include "ServerConnectionHandler.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "WelcomeMessage.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <random>
#include "Chat.hpp"

ServerConnectionHandler::ServerConnectionHandler(Server *server, Chat *chat)
  : server(server), chat(chat) {}

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

  std::string conversation = chat->ToJson().dump();
  
  WelcomeMessage *welcomeMessage = new WelcomeMessage(userColor, conversation);
  server->SendTo(peer, welcomeMessage);

  const int serverChatColor = 8;
  
  ChatMessage newUserMessage("Server", serverChatColor, clientInfo->GetUsername() + " has joined the server.");
  server->Broadcast(&newUserMessage);

  delete message;

  return true;
}
