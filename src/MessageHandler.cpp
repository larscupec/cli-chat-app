#include "MessageHandler.hpp"
#include "Message.hpp"

bool MessageHandler::Handle(Message *message, ENetPeer* peer) {

  bool result = HandleMessage(message, peer);

  if (next && !result) {
    return next->Handle(message, peer);
  }

  return result;
}
