#include "ConnectCommand.hpp"
#include "ChatMode.hpp"
#include "Client.hpp"
#include "Debug.hpp"
#include "ThreadManager.hpp"
#include <string>
#include <thread>
#include "App.hpp"
#include "Console.hpp"

void ConnectCommand::Execute(std::vector<std::string> args) {
  if (args.size() != 2) {
    Debug::LogError("Invalid number of arguments " + std::to_string(args.size())+ " (connect)");
    return;
  }

  std::string ip = args[0];
  int port = std::stoi(args[1]);

  if (client->ConnectTo(ip, port)) {
    std::thread *clientThread = new std::thread(&Client::Listen, client);
    ThreadManager::Add(clientThread);
    ChatMode *chatMode = new ChatMode(client);
    console->SetConsoleMode(chatMode);
  }
}
