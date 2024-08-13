#pragma once

#include "ICommand.hpp"

class Client;
class App;
class Console;

class LeaveCommand : public ICommand {
public:
  LeaveCommand(App *app, Client *client, Console* console) : app(app), client(client), console(console) {}

  virtual void Execute(std::vector<std::string> args) override;
  
private:
  App *app = nullptr;
  Client *client = nullptr;
  Console *console = nullptr;
 
};
