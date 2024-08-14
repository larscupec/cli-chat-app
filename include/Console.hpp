#pragma once

#include "IConsoleMode.hpp"
#include <string>

class App;
class Client;

class Console {
public:
  Console(App *app, Client *client);
  ~Console();

  void ProcessInput();

  void SetConsoleMode(IConsoleMode *consoleMode);

private:
  IConsoleMode *consoleMode = nullptr;
  App *app = nullptr;
  Client *client = nullptr;

  std::string ReadInput();
  void ClearInput();
  void Edit();
};
