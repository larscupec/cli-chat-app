#pragma once

#include "ConsoleMode.hpp"

class Server;

class ServerCommandMode : public ConsoleMode {
public:
  static ServerCommandMode *GetInstance();

  virtual bool HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command (Server)"; }

  void SetServer(Server *server) { this->server = server; }

private:
  ServerCommandMode() {}

  static ServerCommandMode *instance;

  Server *server = nullptr;
};
