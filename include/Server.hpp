#pragma once

#include <enet/enet.h>

class MessageHandler;
class Chat;
class Message;
class UserColorTable;

class Server
{
public:
  ~Server();

  static Server *GetInstance();

  void Start(int port);
  void Stop();

  void SendTo(ENetPeer *peer, Message *message);
  void Broadcast(Message *message);

  Chat *GetChat() { return chat; }
  UserColorTable *GetUserColorTable() { return userColorTable; }
  bool GetIsRunning() { return isRunning; }

private:
  Server();

  static Server *instance;
  
  ENetHost *server = nullptr;

  MessageHandler *messageHandler = nullptr;
  Chat *chat = nullptr;
  UserColorTable *userColorTable = nullptr;

  bool isRunning = false;
};    
