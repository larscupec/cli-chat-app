#include "CommandMode.hpp"
#include "CommandList.hpp"
#include "ConnectCommand.hpp"
#include "Debug.hpp"
#include "ExitCommand.hpp"
#include "LeaveCommand.hpp"
#include <ncurses/ncurses.h>
#include <vector>

CommandMode *CommandMode::instance = nullptr;

CommandMode *CommandMode::GetInstance() {
  if (!instance) {
    instance = new CommandMode();
  }
  return instance;
}

// Taken from
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> SplitString(std::string string,
                                     std::string delimiter) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = string.find(delimiter)) != std::string::npos) {
    token = string.substr(0, pos);
    tokens.push_back(token);
    string.erase(0, pos + delimiter.length());
  }
  tokens.push_back(string);

  return tokens;
}

void CommandMode::HandleInput(std::string input) {
  std::vector<std::string> tokens = SplitString(input, " ");
  std::string command = tokens.front();
  tokens.erase(tokens.begin());
  std::vector<std::string> args = tokens;

  if (command == COMMAND_CONNECT) {
    ConnectCommand connect;
    connect.Execute(args);
  } else if (command == COMMAND_EXIT) {
    ExitCommand exit;
    exit.Execute(args);
  } else if (command == COMMAND_LEAVE) {
    LeaveCommand leave;
    leave.Execute(args);
  } else {
    Debug::Log("Unknown command '" + command + "'");
  }
}
