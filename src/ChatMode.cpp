#include "ChatMode.hpp"
#include "ChatMessage.hpp"
#include "Client.hpp"

ChatMode *ChatMode::instance = nullptr;

ChatMode *ChatMode::GetInstance() {
  if (!instance) {
    instance = new ChatMode();
  }
  return instance;
}

void ChatMode::HandleInput(std::string input) {
  ChatMessage chat(Client::GetInstance()->GetUsername(),
                   Client::GetInstance()->GetUserColor(), input);
  Client::GetInstance()->Send(&chat);
}
