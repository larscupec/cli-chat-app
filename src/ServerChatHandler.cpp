#include "ServerChatHandler.hpp"
#include <enet/enet.h>
#include "Chat.hpp"
#include "ChatMessage.hpp"
#include "Server.hpp"
#include "Debug.hpp"
#include "Message.hpp"

ServerChatHandler::ServerChatHandler(Server *server, Chat *chat)
  : server(server), chat(chat) {}

bool ServerChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  ChatMessage *newChat = (ChatMessage*)message;
  
  chat->Add(newChat);

  Debug::Log("Server: Received a chat message from " + newChat->GetSender() + ": " + newChat->GetContent());

  server->Broadcast(newChat);

  return true;
}
