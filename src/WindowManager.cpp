#include "WindowManager.hpp"
#include "Window.hpp"
#include <ncursesw/ncurses.h>

WindowManager *WindowManager::instance = nullptr;

WindowManager *WindowManager::GetInstance() {
  if (!instance) {
    instance = new WindowManager();
  }
  return instance;
}

WindowManager::WindowManager() {
  // Initialize ncurses and clear stdscr
  initscr();
  clear();

  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  const int CONSOLE_WINDOW_HEIGHT = 3;
  
  chatWindow = new Window("clichatapp", maxHeight, maxWidth / 2);
  debugWindow = new Window("Debug", maxHeight, maxWidth / 2, 0, maxWidth / 2);
  consoleWindow = new Window("Console", CONSOLE_WINDOW_HEIGHT, maxWidth, maxHeight - CONSOLE_WINDOW_HEIGHT, 0);
}

WindowManager::~WindowManager() {
  endwin();
}
