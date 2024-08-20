#pragma once

#include "IConsoleMode.hpp"

class Client;

class ChatMode : public IConsoleMode {
public:

  static ChatMode *GetInstance();
  
  virtual void HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Chat"; }
  
private:
  ChatMode() {}

  static ChatMode *instance;
};
