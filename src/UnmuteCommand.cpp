#include "UnmuteCommand.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "ServerMessage.hpp"
#include "ChatMessage.hpp"
#include "Chat.hpp"

void UnmuteCommand::Execute(std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        Debug::LogError("Invalid number of arguments " + std::to_string(args.size()) + " (unmute)");
        return;
    }

    std::string username = args[0];

    ENetPeer *peer = Server::GetInstance()->GetUserPeer(username);

    if (!peer)
    {
        Debug::LogError("There is no player by the name '" + username + "'");
        return;
    }

    User *user = (User *)peer->data;

    user->Unmute();

    Debug::Log("Unmuted " + username);

    ServerMessage unmutedMessage("You have been unmuted");
    Server::GetInstance()->SendTo(peer, &unmutedMessage);

    ChatMessage *userUnmutedMessage = new ChatMessage("Server", SERVER_CHAT_COLOR, "Unmuted " + username);
    Server::GetInstance()->GetChat()->Add(userUnmutedMessage);
    Server::GetInstance()->Broadcast(userUnmutedMessage);
}