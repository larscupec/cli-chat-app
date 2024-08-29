#pragma once

#include "ConsoleMode.hpp"

class GeneralCommandMode : public ConsoleMode {
public:
  static GeneralCommandMode *GetInstance();
  
  virtual bool HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Command (General)"; }

private:
  GeneralCommandMode() {}

  static GeneralCommandMode *instance;
};
