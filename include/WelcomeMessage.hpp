#pragma once

#include "Color.hpp"
#include "Message.hpp"
#include "MessageType.hpp"

class WelcomeMessage : public Message {
public:
  WelcomeMessage(Color userColor, std::string conversation)
      : Message(MessageType::WELCOME_MESSAGE), userColor(userColor),
        conversation(conversation) {}

  virtual json ToJson() override;

  Color GetUserColor() { return userColor; }
  std::string GetConversation() { return conversation; }

private:
  Color userColor = Color::WHITE;
  std::string conversation = "";
};
