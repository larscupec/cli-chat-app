#pragma once

#include "ConsoleMode.hpp"

class Client;

class ChatMode : public ConsoleMode {
public:

  static ChatMode *GetInstance();
  
  virtual bool HandleInput(std::string input) override;
  virtual std::string ToString() override { return "Chat"; }
  
private:
  ChatMode() {}

  static ChatMode *instance;
};
