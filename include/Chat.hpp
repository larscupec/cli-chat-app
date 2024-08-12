#pragma once

#include <ctime>
#include <map>
#include "ChatMessage.hpp"

class Chat {
public:
  Chat() {}
  ~Chat() {
    for (auto it : messages) {
      delete it.second;
    }
    messages.clear();
  }

  void Add(ChatMessage *message) { messages[nextMessageId++] = message; }

private:
  std::map<unsigned long long, ChatMessage*> messages;
  unsigned long long nextMessageId = 0;
};
