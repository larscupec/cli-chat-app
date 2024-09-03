#include "App.hpp"
#include "Color.hpp"
#include "Debug.hpp"
#include "ThreadManager.hpp"
#include <cctype>
#include <cstdlib>
#include <ncurses.h>
#include <stdexcept>
#include <enet/enet.h>
#include <config.hpp>
#include <iostream>

int main(int argc, char **argv)
{

  bool isServer = false;
  bool isHost = false;

  // Read command line arguments
  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) == "-server" || std::string(argv[i]) == "-s")
    {
      isServer = true;
    }
    else if (std::string(argv[i]) == "-host" || std::string(argv[i]) == "-h")
    {
      isHost = true;
    }
    else if (std::string(argv[i]) == "-version" || std::string(argv[i]) == "-V")
    {
      std::cout << "clichatapp version " << CLICHATAPP_VERSION_MAJOR << "." << CLICHATAPP_VERSION_MINOR << std::endl;
      return 0;
    }
    else
    {
      Debug::Log("Invalid argument '" + std::string(argv[i]) + "'");
    }
  }

  Debug::Log("Initializing ENet...");
  if (enet_initialize() != 0)
  {
    Debug::Log("An error occurred while initializing ENet");
    throw std::runtime_error("An error occurred while initializing ENet");
  }
  atexit(enet_deinitialize);

  initscr();

  if (has_colors())
  {
    start_color();
    if (use_default_colors() == ERR)
    {
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
    }
    else
    {
      init_pair((short)Color::BLACK, COLOR_BLACK, -1);
      init_pair((short)Color::RED, COLOR_RED, -1);
      init_pair((short)Color::GREEN, COLOR_GREEN, -1);
      init_pair((short)Color::YELLOW, COLOR_YELLOW, -1);
      init_pair((short)Color::BLUE, COLOR_BLUE, -1);
      init_pair((short)Color::MAGENTA, COLOR_MAGENTA, -1);
      init_pair((short)Color::CYAN, COLOR_CYAN, -1);
      init_pair((short)Color::WHITE, COLOR_WHITE, -1);
    }
  }
  else
  {
    Debug::LogWarning("Your terminal doesn't support color");
  }

  App::GetInstance()->Run(isHost, isServer);

  ThreadManager::JoinAll();

  endwin();

  return 0;
}
