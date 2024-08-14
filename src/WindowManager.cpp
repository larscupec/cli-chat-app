#include "WindowManager.hpp"
#include "Debug.hpp"
#include "Window.hpp"
#include <ncurses/ncurses.h>
#include <string>
#include "Color.hpp"

WindowManager *WindowManager::instance = nullptr;

WindowManager *WindowManager::GetInstance() {
  if (!instance) {
    instance = new WindowManager();
  }
  return instance;
}

WindowManager::WindowManager() {
  // Initialize ncurses
  initscr();

  if (!has_colors()) {
    Debug::LogWarning("Your terminal doesn't support color");
  }
  else {
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
    }
    else {
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
  
  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  mainWindow = newpad(maxHeight, maxWidth);

  const int CONSOLE_WINDOW_HEIGHT = 3;

  chatWindow = new Window(mainWindow, "clichatapp",
                          maxHeight - CONSOLE_WINDOW_HEIGHT, maxWidth / 2);
  debugWindow =
      new Window(mainWindow, "Debug", maxHeight - CONSOLE_WINDOW_HEIGHT,
                 maxWidth / 2, 0, maxWidth / 2);
  consoleWindow = new Window(mainWindow, "Console", CONSOLE_WINDOW_HEIGHT,
                             maxWidth, maxHeight - CONSOLE_WINDOW_HEIGHT, 0);

  windows.push_back(chatWindow);
  windows.push_back(debugWindow);

  focusedWindowIndex = 0;
  chatWindow->SetHasFocus(true);
}

WindowManager::~WindowManager() {
  delete chatWindow;
  delete consoleWindow;
  delete debugWindow;
  delwin(mainWindow);
  endwin();
}

void WindowManager::FocusNextWindow() {
  GetFocusedWindow()->SetHasFocus(false);
  focusedWindowIndex++;
  if (focusedWindowIndex >= windows.size()) {
    focusedWindowIndex = 0;
  }
  GetFocusedWindow()->SetHasFocus(true);
}
