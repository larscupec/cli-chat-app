#include "ChatMessage.hpp"

ChatMessage::ChatMessage(std::string sender, Color color, std::string content)
  : Message(MessageType::CHAT_MESSAGE), sender(sender), color(color), content(content) {}

json ChatMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["sender"] = sender;
  result["content"] = content;
  result["color"] = (int)color;

  return result;
}
