#include "UserColorMessage.hpp"

json UserColorMessage::ToJson() {
  json result;

  result["type"] = GetTypeAsString();
  result["color"] = color;
  
  return result;
}
