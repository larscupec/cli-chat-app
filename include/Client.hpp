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
  int GetColor() { return color; }

  void SetColor(int color) { this->color = color; }

private:
  std::string username = "";
  int color = 0;

  bool isConnected = false;
  bool isListening = false;

  ENetHost* client = nullptr;
  ENetPeer* connection = nullptr;

  MessageHandler *messageHandler = nullptr;
};   
