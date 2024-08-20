#include "Message.hpp"
#include "ChatMessage.hpp"
#include "ClientInfoMessage.hpp"
#include "Color.hpp"
#include "MessageType.hpp"
#include "WelcomeMessage.hpp"
#include "UnknownMessage.hpp"
#include "DisconnectMessage.hpp"

const std::string CLIENT_INFO_MESSAGE = "client-info";
const std::string CHAT_MESSAGE = "chat-message";
const std::string WELCOME_MESSAGE = "welcome-message";
const std::string UNKNOWN_MESSAGE = "none";
const std::string DISCONNECT_MESSAGE = "disconnect";

Message *Message::Parse(json message) {
  std::string messageType = message["type"].get<std::string>();

  if (messageType == CLIENT_INFO_MESSAGE) {
    std::string username = message["username"].get<std::string>();

    return new ClientInfoMessage(username);
  } else if (messageType == CHAT_MESSAGE) {
    std::string sender = message["sender"].get<std::string>();
    std::string content = message["content"].get<std::string>();
    Color color = (Color)message["color"].get<int>();

    return new ChatMessage(sender, color, content);
  }
  else if (messageType == WELCOME_MESSAGE) {
    Color userColor = (Color)message["userColor"].get<int>();
    std::string conversation = message["conversation"].get<std::string>();

    return new WelcomeMessage(userColor, conversation);
  }
  else if (messageType == DISCONNECT_MESSAGE) {
    return new DisconnectMessage();
  }
  else {
    return new UnknownMessage();
  }
}

std::string Message::GetTypeAsString() {
  switch (GetType()) {
  default: case MessageType::NONE:
    return UNKNOWN_MESSAGE;
  case MessageType::CLIENT_INFO:
    return CLIENT_INFO_MESSAGE;
  case MessageType::CHAT_MESSAGE:
    return CHAT_MESSAGE;
  case MessageType::WELCOME_MESSAGE:
    return WELCOME_MESSAGE;
  case MessageType::DISCONNECT_MESSAGE:
    return DISCONNECT_MESSAGE;
  }
}
