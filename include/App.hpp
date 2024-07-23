#pragma once

#include <string>
#include <vector>

class Client;
class ChatWindow;

class App
{
public:
  App();
  ~App();

  void run();
  void processCommand(std::string command, std::vector<std::string> args);
  
private:
  bool isRunning = false;
  Client* client;
  ChatWindow* chatWindow;
};
