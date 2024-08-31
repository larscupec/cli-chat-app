#include "ServerChatHandler.hpp"
#include <enet/enet.h>
#include "Chat.hpp"
#include "ChatMessage.hpp"
#include "Server.hpp"
#include "Message.hpp"
#include "User.hpp"
#include "ServerMessage.hpp"

bool ServerChatHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::CHAT_MESSAGE) {
    return false;
  }

  User *user = (User*)peer->data;

  if (user->IsMuted())
  {
    ServerMessage userMutedMessage("You are muted");
    Server::GetInstance()->SendTo(peer, &userMutedMessage);

    delete message;
    return true;
  }

  ChatMessage *newChat = (ChatMessage*)message;
  
  server->GetChat()->Add(newChat);

  server->Broadcast(newChat);

  return true;
}
