#include "LeaveCommand.hpp"
#include "Client.hpp"
#include "ClientCommandMode.hpp"
#include "Console.hpp"

void LeaveCommand::Execute(std::vector<std::string> args) {
  Client::GetInstance()->Disconnect();
  Console::GetInstance()->SetMode(ClientCommandMode::GetInstance());
}
