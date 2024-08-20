#pragma once

#include "MessageHandler.hpp"

class LeaveCommand;

class ClientDisconnectHandler : public MessageHandler {
public:
  ClientDisconnectHandler(LeaveCommand *leaveCommand) : leaveCommand(leaveCommand) {}
  ~ClientDisconnectHandler();

  virtual bool HandleMessage(Message *message, ENetPeer *peer) override;

private:
  LeaveCommand *leaveCommand = nullptr;
};
