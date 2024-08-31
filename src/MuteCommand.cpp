#include "MuteCommand.hpp"
#include "Debug.hpp"
#include <stdexcept>
#include "Server.hpp"
#include "User.hpp"
#include "ChatMessage.hpp"
#include "Chat.hpp"
#include "ServerMessage.hpp"

const unsigned int MAX_MUTE_TIME_SEC = 1000000;

void MuteCommand::Execute(std::vector<std::string> args)
{
    if (args.size() > 2 || args.empty())
    {
        Debug::LogError("Invalid number of arguments " + std::to_string(args.size()) + " (mute)");
        return;
    }

    std::string username = args[0];
    unsigned int muteTimeSec;

    try
    {
        if (args.size() == 1)
        {
            muteTimeSec = MAX_MUTE_TIME_SEC;
        }
        else
        {
            muteTimeSec = std::stoi(args[1]);
        }
    }
    catch(const std::invalid_argument& e)
    {
        Debug::LogError("Invalid argument '" + args[1] + "'");
        return;
    }
    
    ENetPeer *peer = Server::GetInstance()->GetUserPeer(username);

    if (!peer)
    {
        Debug::LogError("There is no user by the name '" + username + "'");
        return;
    }

    User *user = (User*)peer->data;

    user->Mute(muteTimeSec);

    std::string muteTimeText = std::to_string(muteTimeSec) + " second";
    if (muteTimeSec > 1)
    {
        muteTimeText += "s";
    }

    Debug::Log("Server: Muted " + username + " for " + muteTimeText);

    ServerMessage mutedMessage("You have been muted for " + std::to_string(muteTimeSec) + " seconds");

    if (muteTimeSec >= MAX_MUTE_TIME_SEC)
    {
        mutedMessage.SetServerMessage("You have been muted");
    }

    Server::GetInstance()->SendTo(peer, &mutedMessage);

    ChatMessage *userMutedMessage = new ChatMessage("Server", SERVER_CHAT_COLOR,
                                                     "Muted " +
                                                     username +
                                                     " for " + std::to_string(muteTimeSec) + " seconds");

    if (muteTimeSec >= MAX_MUTE_TIME_SEC)
    {
        userMutedMessage->SetContent("Muted " + username);
    }

    Server::GetInstance()->GetChat()->Add(userMutedMessage);
    Server::GetInstance()->Broadcast(userMutedMessage);
}