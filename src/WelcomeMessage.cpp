#include "WelcomeMessage.hpp"

json WelcomeMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["userColor"] = (int)userColor;
  result["conversation"] = conversation;

  return result;
}
