#include "Message.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "UserColorMessage.hpp"
#include "MessageType.hpp"
#include "UnknownMessage.hpp"

Message *Message::Parse(json message) {

  std::string messageType = message["type"].get<std::string>();

  if (messageType == "client-info") {
    std::string username = message["username"].get<std::string>();

    return new ClientInfoMessage(username);
  } else if (messageType == "chat-message") {
    std::string sender = message["sender"].get<std::string>();
    std::string content = message["content"].get<std::string>();
    int color = message["color"].get<int>();

    return new ChatMessage(sender, color, content);
  }
  else if (messageType == "user-color") {
    int color = message["color"].get<int>();
    
    return new UserColorMessage(color);
  }
  else {
    return new UnknownMessage();
  }
}

std::string Message::GetTypeAsString() {
  switch (GetType()) {
  default: case MessageType::NONE:
    return "none";
  case MessageType::CLIENT_INFO:
    return "client-info";
  case MessageType::CHAT_MESSAGE:
    return "chat-message";
  case MessageType::COLOR_MESSAGE:
    return "user-color";
  }
}
