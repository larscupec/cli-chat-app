#include "ServerCommandMode.hpp"
#include "CommandList.hpp"
#include "Debug.hpp"
#include "KickCommand.hpp"
#include "StopServerCommand.hpp"
#include "StringHelper.hpp"
#include <vector>
#include "ExitCommand.hpp"

ServerCommandMode *ServerCommandMode::instance = nullptr;

ServerCommandMode *ServerCommandMode::GetInstance() {
  if (!instance) {
    instance = new ServerCommandMode();
  }
  return instance;
}

void ServerCommandMode::HandleInput(std::string input) {
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
  else {
    Debug::Log("Unknown command '" + command + "'");
  }
}
