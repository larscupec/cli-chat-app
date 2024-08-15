#pragma once

#include "Message.hpp"
#include "MessageType.hpp"

class WelcomeMessage : public Message {
public:
  WelcomeMessage(int userColor, std::string conversation)
      : Message(MessageType::WELCOME_MESSAGE), userColor(userColor),
        conversation(conversation) {}

  virtual json ToJson() override;

  int GetUserColor() { return userColor; }
  std::string GetConversation() { return conversation; }

private:
  int userColor = 0;
  std::string conversation = "";
};
