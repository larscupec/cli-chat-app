#include "ServerChatHandler.hpp"
#include <enet/enet.h>
#include "Chat.hpp"
#include "ChatMessage.hpp"
#include "Server.hpp"
#include "Debug.hpp"
#include "Message.hpp"

bool ServerChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage*)message;
  
  server->GetChat()->Add(newChat);

  Debug::Log("Server: Received a chat message from " + newChat->GetSender() + ": " + newChat->GetContent());

  server->Broadcast(newChat);

  return true;
}
