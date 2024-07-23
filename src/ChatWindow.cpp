#include "ChatWindow.hpp"
#include <bits/stdc++.h>
#include <codecvt>
#include <ncurses.h>
#include <string>

#include "Client.hpp"
#include "Color.hpp"
#include "Console.hpp"

ChatWindow::ChatWindow() {
  printPad = newpad(rowcount, 200);
  scanWindow = newwin(3, 200, 12, 0);

  box(printPad, 0, 0);
  box(scanWindow, 0, 0);
  
  keypad(scanWindow, TRUE);
  idlok(printPad, TRUE);
  scrollok(printPad, TRUE);
  noecho();

  initColors();

  // Get terminal size
  getmaxyx(stdscr, mrow, mcol);
}

ChatWindow::~ChatWindow() {
  // Destroy windows
  delwin(scanWindow);
  scanWindow = nullptr;
  delwin(printPad);
  printPad = nullptr;

  rowcount = 2;
  padpos = 0;
}

void ChatWindow::update() {
  Console::getInstance()->displayPadPosition(padpos, rowcount);

  char input[200];
  unsigned short lastCharIdx = 0;
  unsigned short caretPosition = 0; // current string index the cursor is on

  int ch;
  while ((ch = wgetch(scanWindow)) != '\n')
  {
    // Get cursor position
    int x, y;
    getyx(scanWindow, y, x);

    switch (ch) {
    case KEY_LEFT:
      if (x > 4 && caretPosition > 0) {
        wmove(scanWindow, y, --x);
        caretPosition--;
      }
      break;

    case KEY_RIGHT:
      if (caretPosition < lastCharIdx) {
        wmove(scanWindow, y, ++x);
        caretPosition++;
      }
      break;

    case KEY_BACKSPACE:
      if (x > 4) {
        mvwdelch(scanWindow, y, --x);

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
        winsch(scanWindow, ch);
        wmove(scanWindow, y, ++x);

        input[lastCharIdx] = '\0';
        insertChar(input, ch, caretPosition);
        lastCharIdx++;
        caretPosition++;
      }
      break;
    }

    Console::getInstance()->displayCaretPosition(caretPosition, lastCharIdx);
  }

  input[lastCharIdx] = '\0';

  // Check if input is a command (starts with '/')
  if (input[0] == '/') {
    std::string commandStr = input;

    commandStr.erase(0, 1); // Remove '/' character

    std::vector<std::string> args = splitString(commandStr, ' ');
    std::string command = args[0];
    args.erase(args.cbegin()); // Remove the command itslef from the argument list

    processCommand(command, args);
    
  } else {
    // If it's not a command then send a message
    if (isMessageValid(input)) {
      nlohmann::json message;
      message["type"] = "chatMessage";
      message["content"] = input;
      client->send(message.dump());
    }
  }

  // Clear input line
  wmove(scanWindow, 0, 4);
  wclrtoeol(scanWindow);

  Console::getInstance()->displayCaretPosition(caretPosition, lastCharIdx);
}

void ChatWindow::resizePad() {
  wresize(printPad, ++rowcount, mcol);

  if (rowcount - padpos == 14) padpos++;

  prefresh(printPad, padpos, 0, 0, 0, visibleRows, mcol - 1);
}

void ChatWindow::loadConversation(nlohmann::json &data) {
  for (auto &it : data["conversation"]) {
    auto j = nlohmann::json::parse(it.get<std::string>().c_str());

    if (j["type"] == "chat") {
      std::string username = j["username"];
      std::string msg = j["message"];
      short color = j["color"];

      activateColor((Color)color, printPad);
      wprintw(printPad, "%s", username.c_str());
      deactivateColor((Color)color, printPad);
      wprintw(printPad, ": %s\n", msg.c_str());
    } else if (j["type"] == "welcome") {
      std::string msg = j["message"];
      wprintw(printPad, "%s\n", msg.c_str());
    }
    resizePad();
  }
}

void ChatWindow::eraseChar(char *str, int idx) {
  for (size_t i = idx; i <= strlen(str); i++) {
    str[i] = str[i + 1];
  }
}

void ChatWindow::insertChar(char *str, char ch, int idx) {
  size_t i;
  for (i = strlen(str) + 1; i > idx; i--) {
    str[i + 1] = str[i];
  }
  str[i + 1] = str[i];
  str[i] = ch;
}

void ChatWindow::processCommand(std::string command,
                                std::vector<std::string> args) {
  if (command == "leave") {
    // Disconnect from server
    client->disconnect();
  } else {
    mvwprintw(scanWindow, 2, 0, "Unknown command '%s'", command.c_str());
    wmove(scanWindow, 0, 4);
  }
}

bool ChatWindow::isMessageValid(char *msg) {
  for (int i = 0; i < strlen(msg); i++)
  {
    if (!isspace(msg[i]))
      return true;
  }
  return false;
}

void ChatWindow::printMsg(std::string msg) {
  wprintw(printPad, "%s\n", msg.c_str());
  resizePad();
}

void ChatWindow::printChat(std::string username, std::string msg, short color) {
  activateColor((Color)color, printPad);
  wprintw(printPad, "%s", username.c_str());
  deactivateColor((Color)color, printPad);
  wprintw(printPad, ": %s\n", msg.c_str());
  resizePad();
}

std::vector<std::string> ChatWindow::splitString(const std::string &s,
                                                 char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}
