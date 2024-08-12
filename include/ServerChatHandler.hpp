#pragma once

#include "MessageHandler.hpp"

class Chat;
class Server;
class Message;

class ServerChatHandler : public MessageHandler {
public:
  ServerChatHandler(Server *server, Chat* chat);

  virtual bool HandleMessage(Message *message, ENetPeer* peer) override;

private:
  Server* server;
  Chat* chat;
};
