#include "UnbanCommand.hpp"
#include "Server.hpp"
#include "Debug.hpp"
#include "BanList.hpp"
#include <stdexcept>
#include "ChatMessage.hpp"
#include "Chat.hpp"

void UnbanCommand::Execute(std::vector<std::string> args)
{
    if (args.size() != 1)
    {
        Debug::LogError("Invalid number of arguments " + std::to_string(args.size()) + " (ban)");
        return;
    }

    unsigned int address;
    try
    {
        address = std::stoi(args[0]);
    }
    catch(const std::invalid_argument& e)
    {
        Debug::LogError("Invalid address '" + args[0] + "'");
        return;
    }

    BanList *banList = Server::GetInstance()->GetBanList();

    if (!banList->Exists(address))
    {
        Debug::LogError("The address '" + std::to_string(address) + "' isn't banned");
        return;
    }

    std::string username = banList->GetUsername(address);
    banList->Remove(address);

    ChatMessage *userUnbannedMessage = new ChatMessage("Server", SERVER_CHAT_COLOR,
                                                        username +
                                                        " was unbanned from the server");
    Server::GetInstance()->GetChat()->Add(userUnbannedMessage);
    Server::GetInstance()->Broadcast(userUnbannedMessage);

    Debug::Log("Server: Unbanned " + username);
}
