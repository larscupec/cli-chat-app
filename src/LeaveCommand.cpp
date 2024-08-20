#include "LeaveCommand.hpp"
#include "Client.hpp"
#include "CommandMode.hpp"
#include "App.hpp"
#include "Console.hpp"

void LeaveCommand::Execute(std::vector<std::string> args) {
  Client::GetInstance()->Disconnect();
  Console::GetInstance()->SetConsoleMode(CommandMode::GetInstance());
}
