#include "ClientDisconnectHandler.hpp"
#include "LeaveCommand.hpp"
#include <vector>

ClientDisconnectHandler::~ClientDisconnectHandler() { delete leaveCommand; }

bool ClientDisconnectHandler::HandleMessage(Message *message, ENetPeer *peer) {
  leaveCommand->Execute(std::vector<std::string>());
  return true;
}
