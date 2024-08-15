#pragma once

#include "MessageHandler.hpp"

class ClientChatHandler;
class Client;

class ClientWelcomeHandler : public MessageHandler {
public:
  ClientWelcomeHandler(Client *client, ClientChatHandler *clientChatHandler) : client(client), clientChatHandler(clientChatHandler) {}

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;

private:
  Client *client = nullptr;
  ClientChatHandler *clientChatHandler = nullptr;
};
