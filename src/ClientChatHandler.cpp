#include "ClientChatHandler.hpp"
#include "ChatMessage.hpp"
#include "Color.hpp"
#include "ChatWindow.hpp"

bool ClientChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage *)message;

  ChatWindow::ActivateColor((Color)newChat->GetColor());
  ChatWindow::Print(newChat->GetSender());
  ChatWindow::DeactivateColor((Color)newChat->GetColor());
  ChatWindow::PrintLine(": " + newChat->GetContent());

  return true;
}
