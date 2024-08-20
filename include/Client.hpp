#pragma once

#include <string>
#include <enet/enet.h>
#include "Color.hpp"

class Message;
class MessageHandler;

class Client
{
public:
  ~Client();

  static Client *GetInstance();

  bool ConnectTo(std::string ip, int port);
  void Listen();
  void Send(Message *message);
  void Disconnect();

  std::string GetUsername() { return username; }
  bool GetIsConnected() { return isConnected; }
  Color GetUserColor() { return userColor; }

  void SetUsername(std::string username) { this->username = username; }
  void SetUserColor(Color userColor) { this->userColor = userColor; }

private:
  Client();

  static Client *instance;
  
  std::string username = "";
  Color userColor = Color::WHITE;

  bool isConnected = false;
  bool isListening = false;

  ENetHost* client = nullptr;
  ENetPeer* connection = nullptr;

  MessageHandler *messageHandler = nullptr;
};   
