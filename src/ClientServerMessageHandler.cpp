#include "ClientServerMessageHandler.hpp"
#include "ChatWindow.hpp"
#include "ServerMessage.hpp"

bool ClientServerMessageHandler::HandleMessage(Message *message, ENetPeer *peer)
{
    if (message->GetType() != MessageType::SERVER_MESSAGE)
    {
        return false;
    }

    ServerMessage *serverMessage = (ServerMessage*)message;

    ChatWindow::PrintLine(serverMessage->GetServerMessage());

    return true;
}