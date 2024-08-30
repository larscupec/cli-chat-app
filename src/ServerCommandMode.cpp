#include "ServerCommandMode.hpp"
#include "Commands.hpp"
#include "Debug.hpp"
#include "KickCommand.hpp"
#include "StopServerCommand.hpp"
#include "StringHelper.hpp"
#include <vector>
#include "ExitCommand.hpp"
#include "Server.hpp"
#include "BanCommand.hpp"
#include "UnbanCommand.hpp"

ServerCommandMode *ServerCommandMode::instance = nullptr;

ServerCommandMode *ServerCommandMode::GetInstance() {
  if (!instance) {
    instance = new ServerCommandMode();
  }
  return instance;
}

bool ServerCommandMode::HandleInput(std::string input) {
  if (!Server::GetInstance()->GetIsRunning())
  {
    Debug::LogError("The server isn't running");
    return false;
  }

  std::vector<std::string> tokens = StringHelper::SplitString(input, " ");
  std::string command = tokens.front();
  tokens.erase(tokens.begin());
  std::vector<std::string> args = tokens;

  if (command == COMMAND_STOP) {
    StopServerCommand stop;
    stop.Execute(args);
  }
  else if (command == COMMAND_EXIT) {
    ExitCommand exit;
    exit.Execute(args);
  }
  else if (command == COMMAND_KICK) {
    KickCommand kick;
    kick.Execute(args);
  }
  else if (command == COMMAND_BAN) {
    BanCommand ban;
    ban.Execute(args);
  }
  else if (command == COMMAND_UNBAN) {
    UnbanCommand unban;
    unban.Execute(args);
  }
  else {
    return false;
  }

  return true;
}
