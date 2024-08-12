#include "ChatMessage.hpp"

ChatMessage::ChatMessage(std::string sender, std::string content)
  : Message(MessageType::CHAT_MESSAGE), sender(sender), content(content) {}

json ChatMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["sender"] = sender;
  result["content"] = content;

  return result;
}
