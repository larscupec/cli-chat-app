#pragma once

#include "MessageHandler.hpp"

class Message;

class Server;

class ServerConnectionHandler : public MessageHandler
{
public:
  ServerConnectionHandler(Server *server);
  
  virtual bool HandleMessage(Message *message, ENetPeer* peer) override;

private:
  Server *server = nullptr;
};    
