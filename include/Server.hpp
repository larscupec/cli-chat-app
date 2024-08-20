#pragma once

#include <enet/enet.h>

class MessageHandler;
class Chat;
class Message;
class UserColorTable;

class Server
{
public:
  Server(int port);
  ~Server();

  void Start();
  void Stop();

  void SendTo(ENetPeer *peer, Message *message);
  void Broadcast(Message *message);

  Chat *GetChat() { return chat; }
  UserColorTable *GetUserColorTable() { return userColorTable; }

private:
  ENetHost *server = nullptr;
  ENetAddress address;

  MessageHandler *messageHandler = nullptr;
  Chat *chat = nullptr;
  UserColorTable *userColorTable = nullptr;

  bool isRunning = false;
};    
