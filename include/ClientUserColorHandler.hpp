#pragma once

#include "MessageHandler.hpp"

class Client;

class ClientUserColorHandler : public MessageHandler {
public:
  ClientUserColorHandler(Client *client);

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;

private:
  Client *client = nullptr;
};
