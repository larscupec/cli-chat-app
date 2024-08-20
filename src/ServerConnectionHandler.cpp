#include "ServerConnectionHandler.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "WelcomeMessage.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <random>
#include "Chat.hpp"
#include "UserColorTable.hpp"

bool ServerConnectionHandler::HandleMessage(Message *message, ENetPeer *peer) {

  if (message->GetType() != MessageType::CLIENT_INFO) {
    return false;
  }

  ClientInfoMessage *clientInfo = (ClientInfoMessage*)message;

  std::string username = clientInfo->GetUsername();
  Color userColor = Color::BLACK;

  UserColorTable *userColorTable = server->GetUserColorTable();
  Chat *chat = server->GetChat();
  
  if (userColorTable->HasColor(username)) {
    userColor = userColorTable->GetColor(username);
    Debug::Log("Server: " + username + " already has a color");
  }
  else {
    Debug::Log("Server: Assigning a new color to the user: " + username);
    std::random_device device;
    std::mt19937 randomNumberGenerator(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(2, 7);

    userColor = (Color)distribution(randomNumberGenerator);
    userColorTable->Add(username, userColor);
  }

  peer->data = new User(username, userColor);

  Debug::Log("Server: " + username + " has joined the server.");

  std::string conversation = chat->ToJson().dump();
  
  WelcomeMessage *welcomeMessage = new WelcomeMessage(userColor, conversation);
  server->SendTo(peer, welcomeMessage);

  ChatMessage *newUserMessage = new ChatMessage("Server", SERVER_CHAT_COLOR, username + " has joined the server.");
  chat->Add(newUserMessage);
  server->Broadcast(newUserMessage);

  delete message;

  return true;
}
