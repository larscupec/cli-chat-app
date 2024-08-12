#include "Message.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "UnknownMessage.hpp"

Message *Message::Parse(json message) {

  std::string messageType = message["type"].get<std::string>();

  if (messageType == "client-info") {
    std::string username = message["username"].get<std::string>();

    return new ClientInfoMessage(username);
  } else if (messageType == "chat-message") {
    std::string sender = message["sender"].get<std::string>();
    std::string content = message["content"].get<std::string>();

    return new ChatMessage(sender, content);
  } else {
    return new UnknownMessage();
  }
}

std::string Message::GetTypeAsString() {
  switch (GetType()) {
  default: case MessageType::NONE:
    return "none";
    break;
  case MessageType::CLIENT_INFO:
    return "client-info";
    break;
  case MessageType::CHAT_MESSAGE:
    return "chat-message";
    break;
  }
}
