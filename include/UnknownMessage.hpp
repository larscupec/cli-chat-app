#pragma once

#include "Message.hpp"

class UnknownMessage : public Message {
public:
  UnknownMessage() : Message(MessageType::NONE) {}

  virtual json ToJson() override {
    json result;
    
    result["type"] = GetTypeAsString();
    
    return result;
  }
};
