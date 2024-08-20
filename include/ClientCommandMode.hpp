#pragma once

#include "IConsoleMode.hpp"

class ClientCommandMode : public IConsoleMode {
public:
  static ClientCommandMode *GetInstance();
  
  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command (Client)"; }

private:
  ClientCommandMode() {}

  static ClientCommandMode *instance;
};
