#include "WindowManager.hpp"
#include "ChatWindow.hpp"
#include "ConsoleWindow.hpp"
#include "DebugWindow.hpp"
#include "Window.hpp"
#include <vector>

std::vector<Window *> WindowManager::windows;
int WindowManager::focusedWindowIndex = 0;

void WindowManager::FocusNextWindow() {
  windows[focusedWindowIndex]->SetHasFocus(false);
  
  focusedWindowIndex++;

  if (focusedWindowIndex == windows.size()) {
    focusedWindowIndex = 0;
  }

  windows[focusedWindowIndex]->SetHasFocus(true);
}

