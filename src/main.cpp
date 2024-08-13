#include "App.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <thread>
#include "App.hpp"
#include "ThreadManager.hpp"

bool isServer = false;
bool isHost = false;
int serverPort = 1234;

App *app = nullptr;
Server *server = nullptr;

int main(int argc, char **argv) {
  Debug::Log("Starting clichatapp...");
  
  Debug::Log("Initializing ENet...");
  if (enet_initialize() != 0) {
    Debug::Log("An error occurred while initializing ENet");
    throw std::runtime_error("An error occurred while initializing ENet");
  }
  atexit(enet_deinitialize);

  // Read command line arguments
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "--server") {
      isServer = true;
    }
    else if (std::string(argv[i]) == "--host") {
      isHost = true;
    }
    else {
      Debug::Log("Invalid argument '" + std::string(argv[i]) + "'");
    }
  }

  if (!isServer) {
    app = new App();

    if (isHost) {
      server = new Server(serverPort);
      std::thread *serverThread = new std::thread(&Server::Start, server);
      ThreadManager::Add(serverThread);
    }
    
    app->Run();

    if (server) {
      server->Stop();
    }
  }
  else {
    server = new Server(serverPort);
    server->Start();
  }

  ThreadManager::JoinAll();
  
  return 0;
}
