#pragma once

#include "ConsoleMode.hpp"

class ClientCommandMode : public ConsoleMode {
public:
  static ClientCommandMode *GetInstance();
  
  virtual bool HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command (Client)"; }

private:
  ClientCommandMode() {}

  static ClientCommandMode *instance;
};
