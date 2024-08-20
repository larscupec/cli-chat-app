#pragma once

#include "IConsoleMode.hpp"

class Server;

class ServerCommandMode : public IConsoleMode {
public:
  static ServerCommandMode *GetInstance();

  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command (Server)"; }

  void SetServer(Server *server) { this->server = server; }

private:
  ServerCommandMode() {}

  static ServerCommandMode *instance;

  Server *server = nullptr;
};
