#include "ChatMode.hpp"
#include "ChatMessage.hpp"
#include "Client.hpp"

void ChatMode::HandleInput(std::string input) {
  ChatMessage chat(client->GetUsername(), input);
  client->Send(&chat);
}
