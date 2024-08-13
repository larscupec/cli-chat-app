#pragma once

#include "IConsoleMode.hpp"
#include <vector>

class App;
class Client;
class Console;

class CommandMode : public IConsoleMode {
public:
  CommandMode(App *app, Client *client, Console *console)
    : app(app), client(client), console(console) {}

  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command"; }

private:
  App *app = nullptr;
  Client *client = nullptr;
  Console *console = nullptr;

  std::vector<std::string> SplitString(std::string string,
                                       std::string delimiter);
};
