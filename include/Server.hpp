#pragma once

#include <enet/enet.h>
#include <string>

class MessageHandler;
class Chat;
class Message;
class UserColorTable;
class User;

class Server {
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
  ENetPeer *GetUserPeer(std::string username);

private:
  Server();

  static Server *instance;

  ENetHost *server = nullptr;

  MessageHandler *messageHandler = nullptr;
  Chat *chat = nullptr;
  UserColorTable *userColorTable = nullptr;

  bool isRunning = false;
};
