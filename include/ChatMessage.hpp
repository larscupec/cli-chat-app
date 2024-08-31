#pragma once

#include "Color.hpp"
#include "Message.hpp"

class ChatMessage : public Message
{
public:
  ChatMessage(std::string sender, Color color, std::string content);

  virtual json ToJson() override;

  std::string GetSender() { return sender; }
  std::string GetContent() { return content; }
  Color GetColor() { return color; }

  void SetContent(std::string content) { this->content = content; }

private:
  std::string sender = "";
  std::string content = "";
  Color color = Color::WHITE;
};

const Color SERVER_CHAT_COLOR = Color::WHITE;
