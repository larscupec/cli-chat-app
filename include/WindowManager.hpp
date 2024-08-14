#pragma once

#include <ncurses/ncurses.h>
#include <vector>

class Window;

class WindowManager {
public:
  ~WindowManager();

  static WindowManager *GetInstance();

  Window *GetChatWindow() { return chatWindow; }
  Window *GetConsoleWindow() { return consoleWindow; }
  Window *GetDebugWindow() { return debugWindow; }

  void FocusNextWindow();

  Window *GetFocusedWindow() { return windows[focusedWindowIndex]; }

private:
  WindowManager();
  static WindowManager *instance;

  WINDOW *mainWindow = nullptr;

  Window *chatWindow = nullptr;
  Window *consoleWindow = nullptr;
  Window *debugWindow = nullptr;

  size_t focusedWindowIndex = 0;

  std::vector<Window*> windows;
};
