#include "ConnectCommand.hpp"
#include "ChatMode.hpp"
#include "Client.hpp"
#include "Debug.hpp"
#include "ThreadManager.hpp"
#include <string>
#include <thread>
#include "App.hpp"
#include "Console.hpp"
#include <stdexcept>

void ConnectCommand::Execute(std::vector<std::string> args) {
  if (args.size() != 2) {
    Debug::LogError("Invalid number of arguments " + std::to_string(args.size())+ " (connect)");
    return;
  }

  std::string ip = args[0];
  int port = 0;
  
  try
  {
    port = std::stoi(args[1]);
  }
  catch(const std::invalid_argument& e)
  {
    Debug::LogError("Invalid port number '" + args[1] + "'");
    return;
  }

  if (Client::GetInstance()->ConnectTo(ip, port)) {
    std::thread *clientThread = new std::thread(&Client::Listen, Client::GetInstance());
    ThreadManager::Add(clientThread);
    Console::GetInstance()->SetConsoleMode(ChatMode::GetInstance());
  }
}
