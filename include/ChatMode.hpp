#pragma once

#include "IConsoleMode.hpp"

class Client;

class ChatMode : public IConsoleMode {
public:
  ChatMode(Client *client) : client(client) {}

  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Chat"; }
  
private:
  Client *client = nullptr;
};
