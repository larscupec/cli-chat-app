#include "ClientChatHandler.hpp"
#include "ChatMessage.hpp"
#include "ChatWindow.hpp"

bool ClientChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage *)message;

  ChatWindow::ActivateColor(newChat->GetColor());
  ChatWindow::Print(newChat->GetSender());
  ChatWindow::DeactivateColor(newChat->GetColor());
  ChatWindow::PrintLine(": " + newChat->GetContent());

  return true;
}
