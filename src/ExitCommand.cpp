#include "ExitCommand.hpp"
#include <string>
#include "App.hpp"

void ExitCommand::Execute(std::vector<std::string> args) {
  app->Quit();
}
