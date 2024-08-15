#include "App.hpp"
#include "ChatWindow.hpp"
#include "Color.hpp"
#include "ConsoleWindow.hpp"
#include "Debug.hpp"
#include "DebugWindow.hpp"
#include "Server.hpp"
#include "ThreadManager.hpp"
#include <cctype>
#include <cstdlib>
#include <ncurses/ncurses.h>
#include <stdexcept>
#include <thread>
#include "Window.hpp"

const int CONSOLE_HEIGHT = 3;

bool isServer = false;
bool isHost = false;
int serverPort = 1234;

App *app = nullptr;
Server *server = nullptr;

int main(int argc, char **argv) {

  // Read command line arguments
  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "--server" || std::string(argv[i]) == "-S") {
      isServer = true;
    } else if (std::string(argv[i]) == "--host" ||
               std::string(argv[i]) == "-H") {
      isHost = true;
    } else {
      Debug::Log("Invalid argument '" + std::string(argv[i]) + "'");
    }
  }

  Debug::Log("Initializing ENet...");
  if (enet_initialize() != 0) {
    Debug::Log("An error occurred while initializing ENet");
    throw std::runtime_error("An error occurred while initializing ENet");
  }
  atexit(enet_deinitialize);

  if (!isServer) {
    initscr();

    int maxWidth = getmaxx(stdscr);
    int maxHeight = getmaxy(stdscr);

    WINDOW *mainWindow = newpad(maxHeight, maxWidth);

    Window *chatWindow = new Window(mainWindow, "Chat", maxHeight - CONSOLE_HEIGHT, maxWidth / 2);
    Window *debugWindow = new Window(mainWindow, "Debug", maxHeight - CONSOLE_HEIGHT, maxWidth / 2, 0, maxWidth / 2);
    Window *consoleWindow = new Window(mainWindow, "Console", CONSOLE_HEIGHT, maxWidth, maxHeight - CONSOLE_HEIGHT, 0);

    DebugWindow::SetWindow(debugWindow);
    ConsoleWindow::SetWindow(consoleWindow);
    ChatWindow::SetWindow(chatWindow);

    Debug::Log("Starting clichatapp...");

    if (has_colors()) {
      start_color();
      if (use_default_colors() == ERR) {
        init_pair((short)Color::BLACK, COLOR_BLACK, COLOR_WHITE);
        init_pair((short)Color::RED, COLOR_RED, COLOR_BLACK);
        init_pair((short)Color::GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair((short)Color::YELLOW, COLOR_YELLOW, COLOR_BLACK);
        init_pair((short)Color::BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair((short)Color::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair((short)Color::CYAN, COLOR_CYAN, COLOR_BLACK);
        init_pair((short)Color::WHITE, COLOR_WHITE, COLOR_BLACK);
        Debug::LogWarning(
            "Your terminal doesn't support the use of default colors");
      } else {
        init_pair((short)Color::BLACK, COLOR_BLACK, -1);
        init_pair((short)Color::RED, COLOR_RED, -1);
        init_pair((short)Color::GREEN, COLOR_GREEN, -1);
        init_pair((short)Color::YELLOW, COLOR_YELLOW, -1);
        init_pair((short)Color::BLUE, COLOR_BLUE, -1);
        init_pair((short)Color::MAGENTA, COLOR_MAGENTA, -1);
        init_pair((short)Color::CYAN, COLOR_CYAN, -1);
        init_pair((short)Color::WHITE, COLOR_WHITE, -1);
      }
    } else {
      Debug::LogWarning("Your terminal doesn't support color");
    }

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
  } else {
    server = new Server(serverPort);
    server->Start();
  }

  ThreadManager::JoinAll();

  return 0;
}
