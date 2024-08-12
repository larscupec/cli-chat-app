#pragma once

#include "Message.hpp"

class ClientInfoMessage : public Message {
public:
  ClientInfoMessage(std::string username);

  virtual json ToJson() override;

  std::string GetUsername() { return username; }

private:
  std::string username = "";
};
