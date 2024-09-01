#include "ClientCommandMode.hpp"
#include "Commands.hpp"
#include "ConnectCommand.hpp"
#include "Debug.hpp"
#include "ExitCommand.hpp"
#include "LeaveCommand.hpp"
#include "StringHelper.hpp"
#include <ncurses.h>
#include <vector>
#include "OpenWindowCommand.hpp"

ClientCommandMode *ClientCommandMode::instance = nullptr;

ClientCommandMode *ClientCommandMode::GetInstance() {
  if (!instance) {
    instance = new ClientCommandMode();
  }
  return instance;
}

bool ClientCommandMode::HandleInput(std::string input) {
  std::vector<std::string> tokens = StringHelper::SplitString(input, " ");
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
    return false;
  }
  
  return true;
}
