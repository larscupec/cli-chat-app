#pragma once

#include "Message.hpp"

class ChatMessage : public Message
{
public:
  ChatMessage(std::string sender, int color, std::string content);

  virtual json ToJson() override;

  std::string GetSender() { return sender; }
  std::string GetContent() { return content; }
  int GetColor() { return color; }

private:
  std::string sender = "";
  std::string content = "";
  int color = 0;
};    
