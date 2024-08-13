#pragma once

#include <string>
#include <enet/enet.h>

class Message;
class MessageHandler;

class Client
{
public:
  Client(std::string username);
  ~Client();

  bool ConnectTo(std::string ip, int port);
  void Listen();
  void Send(Message *message);
  void Disconnect();

  std::string GetUsername() { return username; }
  bool GetIsConnected() { return isConnected; }

private:
  std::string username = "";

  bool isConnected = false;
  bool isListening = false;

  ENetHost* client = nullptr;
  ENetPeer* connection = nullptr;

  MessageHandler *messageHandler = nullptr;
};   
