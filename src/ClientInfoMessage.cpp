#include "ClientInfoMessage.hpp"
#include "MessageType.hpp"

ClientInfoMessage::ClientInfoMessage(std::string username)
  : Message(MessageType::CLIENT_INFO), username(username) {}

json ClientInfoMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["username"] = username;

  return result;
}
