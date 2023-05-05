#pragma once

#include <string>

typedef struct _win_st WINDOW;

class ChatConsole
{
private:

public:
    ChatConsole() {};
    ~ChatConsole() {};

    void moveToOutput();
    void clearCommandOutput();
    void chatDebug(std::string);
    void debugPadPosition(int, int);
    void debugCaretPosition(unsigned short, unsigned short);

    WINDOW* scanWin = nullptr;
};
