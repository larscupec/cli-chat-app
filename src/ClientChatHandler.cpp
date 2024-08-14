#include "ClientChatHandler.hpp"
#include "ChatMessage.hpp"
#include "Color.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"

bool ClientChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage *)message;

  Window *chatWindow = WindowManager::GetInstance()->GetChatWindow();

  chatWindow->ActivateColor((Color)newChat->GetColor());
  chatWindow->Print(newChat->GetSender());
  chatWindow->DeactivateColor((Color)newChat->GetColor());
  chatWindow->PrintLine(": " + newChat->GetContent());

  return true;
}
