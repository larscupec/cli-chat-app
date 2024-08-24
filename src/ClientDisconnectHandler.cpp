#include "ClientDisconnectHandler.hpp"
#include "ChatWindow.hpp"
#include "DisconnectMessage.hpp"
#include "LeaveCommand.hpp"
#include <vector>

ClientDisconnectHandler::~ClientDisconnectHandler() { delete leaveCommand; }

bool ClientDisconnectHandler::HandleMessage(Message *message, ENetPeer *peer) {
  DisconnectMessage *disconnectMessage = (DisconnectMessage*)message;

  ChatWindow::PrintLine("Disconnected by the server. Reason: " + disconnectMessage->GetReason());

  leaveCommand->Execute(std::vector<std::string>());

  return true;
}
