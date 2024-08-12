#pragma once

#include <enet/enet.h>

class MessageHandler;
class Chat;
class Message;

class Server
{
public:
  Server(int port);
  ~Server();

  void Start();
  void Stop();

  void SendTo(ENetPeer *peer, Message *message);
  void Broadcast(Message *message);

private:
  ENetHost *server = nullptr;
  ENetAddress address;

  MessageHandler *messageHandler = nullptr;
  Chat *chat = nullptr;

  bool isRunning = false;
};    
