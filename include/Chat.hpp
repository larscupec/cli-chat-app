#pragma once

#include <ctime>
#include <vector>
#include "ChatMessage.hpp"

class Chat {
public:
  Chat() {}
  ~Chat();

  void Add(ChatMessage *message) { messages.push_back(message); }

  json ToJson();

private:
  std::vector<ChatMessage*> messages;
};
