#pragma once

#include <string>
#include <vector>
#include "../include/nlohmann/json.hpp"

typedef struct _win_st WINDOW;

class Client;
class ChatConsole;

class ChatWindow
{
private:
    int mrow;
    int mcol;
    int padpos = 0;
    int rowcount = 2;
    int visibleRows = 10;

    ChatConsole* cCon = nullptr;

public:
    ChatWindow() {};
    ~ChatWindow() {};

    void init();
    void update();
    void destroy();

    void resizePad();
    void loadConversation(nlohmann::json&);
    bool validMessage(char*);
    void processCommand(std::string, std::vector<std::string>);
    void printMsg(std::string);
    void printChat(std::string, std::string, short);

    // Null-terminate the string before calling these!
    void eraseChar(char*, int);
    void insertChar(char*, char, int);

    WINDOW* scanWin = nullptr;
    WINDOW* printPad = nullptr;

    Client* client = nullptr;
};
