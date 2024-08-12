#include "ClientChatHandler.hpp"
#include "ChatMessage.hpp"
#include "Console.hpp"

bool ClientChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage *)message;

  Console::WriteLine(newChat->GetSender() + ": " + newChat->GetContent());

  return true;
}
