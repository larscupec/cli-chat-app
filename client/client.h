#pragma once

#include <string>

typedef struct _ENetHost EnetHost;
typedef struct _ENetPeer ENetPeer;

class ChatWindow;

class Client
{
private:
    EnetHost* client = nullptr;
    ENetPeer* peer = nullptr;

public:
    Client() {};
    ~Client() {};

    int init();
    void update();
    void destroy();

    void connect(std::string, int);
    void disconnect();
    void send(std::string);

    void loadClientInfo();

    bool connected = false;
    std::string username;
    std::string autoconnectIp = "";

    ChatWindow* cWin = nullptr;
};
