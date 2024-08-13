#include "ClientChatHandler.hpp"
#include "ChatMessage.hpp"
#include "WindowManager.hpp"
#include "Window.hpp"

bool ClientChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage *)message;

  WindowManager::GetInstance()->GetChatWindow()->PrintLine(newChat->GetSender() + ": " + newChat->GetContent());

  return true;
}
