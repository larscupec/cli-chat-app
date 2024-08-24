#include "KickCommand.hpp"
#include "ChatMessage.hpp"
#include "Debug.hpp"
#include "DisconnectMessage.hpp"
#include "Server.hpp"
#include "User.hpp"
#include <vector>

void KickCommand::Execute(std::vector<std::string> args) {
  if (args.empty()) {
    Debug::LogError("Invalid number of arguments " +
                    std::to_string(args.size()) + " (kick)");
    return;
  }

  DisconnectMessage disconnectMessage("You were kicked from the server");

  std::string username = args.front();

  ENetPeer *peer = Server::GetInstance()->GetUserPeer(username);

  if (!peer) {
    Debug::LogError("No user with username: " + username);
    return;
  }

  Server::GetInstance()->SendTo(peer, &disconnectMessage);

  User *user = (User *)peer->data;

  ChatMessage playerKickedMessage("Server", SERVER_CHAT_COLOR,
                                  user->GetUsername() +
                                      " was kicked from the server");

  Server::GetInstance()->Broadcast(&playerKickedMessage);

  Debug::Log("Server: Kicked " + username + " from the server");
}
