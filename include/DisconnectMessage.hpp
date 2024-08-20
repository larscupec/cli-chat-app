#pragma once

#include "Message.hpp"
#include "MessageType.hpp"

class DisconnectMessage : public Message {
public:
  DisconnectMessage() : Message(MessageType::DISCONNECT_MESSAGE) {}

  virtual json ToJson() override {
    json result;

    result["type"] = GetTypeAsString();

    return result;
  }
};
