#pragma once

#include <vector>

class Window;

class WindowManager {
public:
  WindowManager() = delete;
  
  static void Add(Window *window) { windows.push_back(window); }

  static void FocusNextWindow();

  static Window *GetFocusedWindow() { return windows[focusedWindowIndex]; }

private: 
  static std::vector<Window*> windows;
  static int focusedWindowIndex;
};
