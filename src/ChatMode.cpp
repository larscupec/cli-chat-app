#include "ChatMode.hpp"
#include "ChatMessage.hpp"
#include "Client.hpp"

void ChatMode::HandleInput(std::string input) {
  ChatMessage chat(client->GetUsername(), client->GetUserColor(), input);
  client->Send(&chat);
}
