#pragma once

#include <enet/enet.h>
#include "json/json.hpp"

using nlohmann::json;

class Message;

class MessageHandler
{
public:
  virtual ~MessageHandler() { delete next; }

  bool Handle(Message *message, ENetPeer* peer);
  
  void SetNext(MessageHandler *next) { this->next = next; }

private:
  MessageHandler *next = nullptr;

protected:
  virtual bool HandleMessage(Message *message, ENetPeer* peer) = 0;
};
