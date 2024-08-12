#pragma once

#include "MessageHandler.hpp"

class ClientChatHandler : public MessageHandler {
public:
  ClientChatHandler() {}

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;
};
