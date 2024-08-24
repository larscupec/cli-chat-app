#pragma once

#include "Message.hpp"
#include "MessageType.hpp"

class DisconnectMessage : public Message {
public:
  DisconnectMessage(std::string reason)
      : reason(reason), Message(MessageType::DISCONNECT_MESSAGE) {}

  virtual json ToJson() override {
    json result;

    result["type"] = GetTypeAsString();
    result["reason"] = reason;

    return result;
  }

  std::string GetReason() { return reason; }

private:
  std::string reason = "";
};
