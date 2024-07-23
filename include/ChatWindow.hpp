#pragma once

#include "json.hpp"
#include <string>
#include <vector>

typedef struct _win_st WINDOW;

class Client;
class Console;

class ChatWindow {
private:
  int mrow;
  int mcol;
  int padpos = 0;
  int rowcount = 2;
  int visibleRows = 10;
  WINDOW *scanWindow = nullptr;
  WINDOW *printPad = nullptr;
  Client *client = nullptr;
  
public:
  ChatWindow();
  ~ChatWindow();

  void update();
  void resizePad();
  void loadConversation(nlohmann::json &);
  bool isMessageValid(char *message);
  void processCommand(std::string, std::vector<std::string>);
  void printMsg(std::string);
  void printChat(std::string, std::string, short);

  // Null-terminate the string before calling these!
  void eraseChar(char *, int);
  void insertChar(char *, char, int);

  std::vector<std::string> splitString(const std::string &s, char delim);
};
