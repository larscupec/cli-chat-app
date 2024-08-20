#include "ClientDisconnectHandler.hpp"
#include "ChatWindow.hpp"
#include "LeaveCommand.hpp"
#include <vector>

ClientDisconnectHandler::~ClientDisconnectHandler() { delete leaveCommand; }

bool ClientDisconnectHandler::HandleMessage(Message *message, ENetPeer *peer) {
  ChatWindow::PrintLine("Disconnected by the server");
  leaveCommand->Execute(std::vector<std::string>());
  return true;
}
