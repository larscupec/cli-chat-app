#include "chatWindow.h"
#include <ncurses.h>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

#include "colors.h"
#include "client.h"
#include "chatConsole.h"

void ChatWindow::init()
{
    printPad = newpad(rowcount, 200);
    scanWin = newwin(3, 200, 12, 0);

    keypad(scanWin, TRUE);
    idlok(printPad, TRUE);
    scrollok(printPad, TRUE);
    noecho();

    // Initialize all colors
    initColors();

    // Get terminal size
    getmaxyx(stdscr, mrow, mcol);

    cCon = new ChatConsole();
    cCon->scanWin = scanWin;
}

void ChatWindow::update()
{
    cCon->debugPadPosition(padpos, rowcount);

    char input[200];
    unsigned short lastCharIdx = 0;
    unsigned short caretPosition = 0;   // current string index the cursor is on

    int ch;
    while ((ch = wgetch(scanWin)) != '\n') {

        // Get cursor position
        int x, y;
        getyx(scanWin, y, x);

        switch (ch)
        {
        case KEY_LEFT:
            if (x > 4 && caretPosition > 0) {
                wmove(scanWin, y, --x);
                caretPosition--;
            }
            break;

        case KEY_RIGHT:
            if (caretPosition < lastCharIdx) {
                wmove(scanWin, y, ++x);
                caretPosition++;
            }
            break;

        case KEY_BACKSPACE:
            if (x > 4) {
                mvwdelch(scanWin, y, --x);

                if (lastCharIdx > 0) {
                    input[lastCharIdx] = '\0';
                    eraseChar(input, --caretPosition);
                    lastCharIdx--;
                }
            }
            break;

        case KEY_UP:
            if (padpos > 0) {
                padpos--;
                prefresh(printPad, padpos, 0, 0, 0, visibleRows, mcol);
            }
            break;

        case KEY_DOWN:
            if (padpos < rowcount - 3) {
                padpos++;
                prefresh(printPad, padpos, 0, 0, 0, visibleRows, mcol);
            }
            break;
        
        default:
            if (lastCharIdx != 199) {
                winsch(scanWin, ch);
                wmove(scanWin, y, ++x);

                input[lastCharIdx] = '\0';
                insertChar(input, ch, caretPosition);
                lastCharIdx++;
                caretPosition++;
            }
            break;
        }

        cCon->debugCaretPosition(caretPosition, lastCharIdx);
    }

    input[lastCharIdx] = '\0';

    // Check for command
    if (input[0] == '/')
    {
        std::string inputStr = input;

        // Remove '/' character
        inputStr.erase(0, 1);
        
        std::vector<std::string> args;
        boost::split(args, inputStr, boost::is_any_of(" "));
        std::string command = args[0];
        // Remove the first command
        args[0] = args[args.size() - 1];
        args.pop_back();

        processCommand(command, args);
    }
    else {
        // Send message
        if (validMessage(input)) {
            nlohmann::json message;
            message["type"] = "chatMessage";
            message["content"] = input;

            client->send(message.dump());
        }
    }

    // Clear input line
    wmove(scanWin, 0, 4);
    wclrtoeol(scanWin);

    cCon->debugCaretPosition(caretPosition, lastCharIdx);
}

void ChatWindow::destroy()
{
    // Destroy windows
    delwin(printPad);
    delwin(scanWin);
    printPad = nullptr;
    scanWin = nullptr;

    rowcount = 2;
    padpos = 0;

    delete cCon;
}

void ChatWindow::resizePad()
{
    wresize(printPad, ++rowcount, mcol);

    if (rowcount - padpos == 14)
        padpos++;

    prefresh(printPad, padpos, 0, 0, 0, visibleRows, mcol - 1);
}

void ChatWindow::loadConversation(nlohmann::json& data)
{
    for (auto& it : data["conversation"])
    {
        auto j = nlohmann::json::parse(it.get<std::string>().c_str());

        if (j["type"] == "chat") {
            std::string username = j["username"];
            std::string msg = j["message"];
            short color = j["color"];

            activateColor((Color)color, printPad);
            wprintw(printPad, "%s", username.c_str());
            deactivateColor((Color)color, printPad);
            wprintw(printPad, ": %s\n", msg.c_str());
        }
        else if (j["type"] == "welcome") {
            std::string msg = j["message"];
            wprintw(printPad, "%s\n", msg.c_str());
        }
        resizePad();
    }
}

void ChatWindow::eraseChar(char* str, int idx)
{
    for (size_t i = idx; i <= strlen(str); i++)
    {
        str[i] = str[i + 1];
    }
}

void ChatWindow::insertChar(char* str, char ch, int idx)
{
    size_t i;
    for (i = strlen(str) + 1; i > idx; i--)
    {
        str[i + 1] = str[i];
    }
    str[i + 1] = str[i];
    str[i] = ch;
}

void ChatWindow::processCommand(std::string command, std::vector<std::string> args)
{
    if (command == "leave") {
        // Disconnect from server
        client->disconnect();
    }
    else {
        mvwprintw(scanWin, 2, 0, "Unknown command");
        wmove(scanWin, 0, 4);
    }
}

bool ChatWindow::validMessage(char* msg)
{
    for (int i = 0; i < strlen(msg); i++) {
        if (!isspace(msg[i])) return true;
    }
    return false;
}

void ChatWindow::printMsg(std::string msg)
{
    wprintw(printPad, "%s\n", msg.c_str());
    resizePad();
}

void ChatWindow::printChat(std::string username, std::string msg, short color)
{
    activateColor((Color)color, printPad);
    wprintw(printPad, "%s", username.c_str());
    deactivateColor((Color)color, printPad);
    wprintw(printPad, ": %s\n", msg.c_str());
    resizePad();
}
