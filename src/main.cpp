#include "App.hpp"
#include "Debug.hpp"
#include "Server.hpp"
#include "enet/enet.h"
#include <cstdlib>
#include <stdexcept>
#include <thread>

int main(void) {
  // Debug::SetWriteToConsole(true);
  Debug::Log("Starting clichatapp...");

  if (enet_initialize() != 0) {
    Debug::Log("An error occurred while initializing ENet");
    throw std::runtime_error("An error occurred while initializing ENet");
  }
  atexit(enet_deinitialize);

  Server server(1234);
  std::thread serverThread(&Server::Start, &server);
  
  App app;
  app.Run();

  serverThread.join();
  
  return 0;
}
