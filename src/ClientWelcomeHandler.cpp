#include "ChatMessage.hpp"
#include "ChatWindow.hpp"
#include "Client.hpp"
#include "ClientWelcomeHandler.hpp"
#include "Message.hpp"
#include "MessageType.hpp"
#include "WelcomeMessage.hpp"
#include "ClientChatHandler.hpp"

bool ClientWelcomeHandler::HandleMessage(Message *message, ENetPeer *peer) {
  if (message->GetType() != MessageType::WELCOME_MESSAGE) {
    return false;
  }

  WelcomeMessage *welcomeMessage = (WelcomeMessage *)message;

  Client::GetInstance()->SetUserColor(welcomeMessage->GetUserColor());

  json conversation = json::parse(welcomeMessage->GetConversation());

  ChatWindow::Clear();

  for (json::iterator it = conversation.begin(); it != conversation.end(); ++it) {
    Message *message = Message::Parse(*it);
    ChatMessage *chat = (ChatMessage *)message;
    clientChatHandler->HandleMessage(chat, peer);
  }

  return true;
}
