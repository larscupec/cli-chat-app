#include "Chat.hpp"

Chat::~Chat() {
  for (auto message : messages) {
    delete message;
  }
  messages.clear();
}

json Chat::ToJson() {
  json result = json::array();
  
  for (auto message : messages) {
    result.push_back(message->ToJson());
  }

  return result;
}
