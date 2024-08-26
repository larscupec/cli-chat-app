#pragma once

#include <vector>
#include <string>

class Window;

const int CONSOLE_HEIGHT = 3;

class WindowManager {
public:
  WindowManager() = delete;
  
  static void Add(Window *window) { windows.push_back(window); }
  static void FocusNextWindow();
  static void CloseFocusedWindow();
  static void OpenWindow(std::string windowTitle);

  static Window *GetFocusedWindow() { return windows[focusedWindowIndex]; }

private: 
  static std::vector<Window*> windows;
  static int focusedWindowIndex;

  static void FocusNextNotConsole();
  static Window *Find(std::string windowTitle);
  static void Focus(Window *window);
  static bool IsOnlyConsoleOpen();
  static void Maximize(Window *window);
  static void SplitToRight(Window *window);
  static void SplitToLeft(Window *window);
};
