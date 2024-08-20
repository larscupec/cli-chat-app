#pragma once

#include "MessageHandler.hpp"

class Server;
class Message;

class ServerChatHandler : public MessageHandler {
public:
  ServerChatHandler(Server *server) : server(server) {}

  virtual bool HandleMessage(Message *message, ENetPeer* peer) override;

private:
  Server* server;
};
