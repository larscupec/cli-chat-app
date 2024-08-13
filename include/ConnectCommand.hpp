#pragma once

#include "ICommand.hpp"

class Console;
class Client;

class ConnectCommand : public ICommand {
public:
  ConnectCommand(Console *console, Client* client) : console(console), client(client) {}

  virtual void Execute(std::vector<std::string> args) override;

private:
  Console *console = nullptr;
  Client* client = nullptr;
};
