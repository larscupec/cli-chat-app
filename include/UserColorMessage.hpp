#pragma once

#include "Message.hpp"

class UserColorMessage : public Message {
public:
  UserColorMessage(int color) : Message(MessageType::COLOR_MESSAGE), color(color) {}

  virtual json ToJson() override;

  int GetColor() { return color; }
  
private:
  int color = 0;
};
