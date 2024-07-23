#pragma once

#include <string>

typedef struct _ENetHost EnetHost;
typedef struct _ENetPeer ENetPeer;

class ChatWindow;

class Client {
private:  
  bool isConnected = false;
  std::string autoconnectIP = "";
  int autoconnectPort = 0;
  EnetHost *client = nullptr;
  ENetPeer *peer = nullptr;
  ChatWindow *chatWindow = nullptr;

public:
  Client(ChatWindow* chatWindow);
  ~Client();

  void connect(std::string ip, int port);
  void update();
  void disconnect();
  void send(std::string message);

  void loadClientInfo();
  void tryAutoConnect();

  bool getIsConnected() { return isConnected; }

  std::string username = "user";
};
