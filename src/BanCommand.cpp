#include "BanCommand.hpp"
#include "Server.hpp"
#include "Debug.hpp"
#include "BanList.hpp"
#include "DisconnectMessage.hpp"
#include "ChatMessage.hpp"
#include "Chat.hpp"

void BanCommand::Execute(std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        Debug::LogError("Invalid number of arguments " + std::to_string(args.size()) + " (ban)");
        return;
    }

    std::string username = args[0];

    ENetPeer *peer = Server::GetInstance()->GetUserPeer(username);

    if (!peer)
    {
        Debug::LogError("There is no user by the name: " + username);
        return;
    }

    Server::GetInstance()->GetBanList()->Add(peer->address.host, username);

    DisconnectMessage banMessage("You got banned");
    Server::GetInstance()->SendTo(peer, &banMessage);

    ChatMessage *userBannedMessage = new ChatMessage("Server", SERVER_CHAT_COLOR,
                                                      username +
                                                      " was banned from the server");
    Server::GetInstance()->GetChat()->Add(userBannedMessage);
    Server::GetInstance()->Broadcast(userBannedMessage);

    Debug::Log("Server: Banned " + username + " from the server");
}
