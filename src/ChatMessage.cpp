#include "ChatMessage.hpp"

ChatMessage::ChatMessage(std::string sender, int color, std::string content)
  : Message(MessageType::CHAT_MESSAGE), sender(sender), color(color), content(content) {}

json ChatMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["sender"] = sender;
  result["content"] = content;
  result["color"] = color;

  return result;
}
