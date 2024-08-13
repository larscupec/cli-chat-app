#include "LeaveCommand.hpp"
#include "Client.hpp"
#include "CommandMode.hpp"
#include "App.hpp"
#include "Console.hpp"

void LeaveCommand::Execute(std::vector<std::string> args) {
  client->Disconnect();
  CommandMode *commandMode = new CommandMode(app, client, console);
  console->SetConsoleMode(commandMode);
}
