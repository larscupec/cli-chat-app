#pragma once

#include "IConsoleMode.hpp"

class CommandMode : public IConsoleMode {
public:
  static CommandMode *GetInstance();
  
  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command"; }

private:
  CommandMode() {}

  static CommandMode *instance;
};
