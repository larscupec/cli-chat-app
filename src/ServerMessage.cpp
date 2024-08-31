#include "ServerMessage.hpp"

json ServerMessage::ToJson()
{
    json result;

    result["type"] = GetTypeAsString();
    result["message"] = message;

    return result;
}