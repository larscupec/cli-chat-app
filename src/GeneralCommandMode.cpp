#include "GeneralCommandMode.hpp"
#include "Commands.hpp"
#include "ConnectCommand.hpp"
#include "Debug.hpp"
#include "ExitCommand.hpp"
#include "LeaveCommand.hpp"
#include "StringHelper.hpp"
#include <ncurses/ncurses.h>
#include <vector>
#include "OpenWindowCommand.hpp"

GeneralCommandMode *GeneralCommandMode::instance = nullptr;

GeneralCommandMode *GeneralCommandMode::GetInstance() {
  if (!instance) {
    instance = new GeneralCommandMode();
  }
  return instance;
}

bool GeneralCommandMode::HandleInput(std::string input) {
  std::vector<std::string> tokens = StringHelper::SplitString(input, " ");
  std::string command = tokens.front();
  tokens.erase(tokens.begin());
  std::vector<std::string> args = tokens;

  if (command == COMMAND_OPEN_WINDOW) {
    OpenWindowCommand openWindow;
    openWindow.Execute(args);
  } else {
    return false;
  }
  
  return true;
}
