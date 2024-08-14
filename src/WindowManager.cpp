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
  refresh();

  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  mainWindow = newpad(maxHeight, maxWidth);

  const int CONSOLE_WINDOW_HEIGHT = 3;
  
  chatWindow = new Window(mainWindow, "clichatapp", maxHeight - CONSOLE_WINDOW_HEIGHT, maxWidth / 2);
  debugWindow = new Window(mainWindow, "Debug", maxHeight - CONSOLE_WINDOW_HEIGHT, maxWidth / 2, 0, maxWidth / 2);
  consoleWindow = new Window(mainWindow, "Console", CONSOLE_WINDOW_HEIGHT, maxWidth, maxHeight - CONSOLE_WINDOW_HEIGHT, 0);

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
