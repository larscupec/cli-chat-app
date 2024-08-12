#pragma once

#include "Message.hpp"

class ChatMessage : public Message
{
public:
  ChatMessage(std::string sender, std::string content);

  virtual json ToJson() override;

  std::string GetSender() { return sender; }
  std::string GetContent() { return content; }

private:
  std::string sender = "";
  std::string content = "";
};    
