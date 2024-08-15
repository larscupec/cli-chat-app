#pragma once

#include "MessageHandler.hpp"

class Message;

class Server;
class Chat;

class ServerConnectionHandler : public MessageHandler {
public:
  ServerConnectionHandler(Server *server, Chat *chat);

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;

private:
  Server *server = nullptr;
  Chat *chat = nullptr;
};
