#pragma once

#include "json/json.hpp"
#include <string>
#include "MessageType.hpp"

using nlohmann::json;

class Message
{
public:
  Message(MessageType type) : type(type) {}
  virtual ~Message() {}

  static Message* Parse(json message);
  virtual json ToJson() = 0;

  MessageType GetType() { return type; }
  std::string GetTypeAsString();

private:
  MessageType type = MessageType::NONE;
};    
