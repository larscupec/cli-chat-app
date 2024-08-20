#pragma once

#include "MessageHandler.hpp"

class ClientChatHandler;

class ClientWelcomeHandler : public MessageHandler {
public:
  ClientWelcomeHandler(ClientChatHandler *clientChatHandler) : clientChatHandler(clientChatHandler) {}

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;

private:
  ClientChatHandler *clientChatHandler = nullptr;
};
