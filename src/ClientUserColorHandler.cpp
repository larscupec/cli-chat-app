#include "ClientUserColorHandler.hpp"
#include "UserColorMessage.hpp"
#include "Message.hpp"
#include "MessageType.hpp"
#include "Client.hpp"

ClientUserColorHandler::ClientUserColorHandler(Client *client) : client(client) {}

bool ClientUserColorHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::COLOR_MESSAGE) {
    return false;
  }

  UserColorMessage *userColorMessage = (UserColorMessage *)message;

  client->SetColor(userColorMessage->GetColor());

  return true;
}
