#include "StopServerCommand.hpp"
#include "Server.hpp"

void StopServerCommand::Execute(std::vector<std::string> args) {
  Server::GetInstance()->Stop();
}
