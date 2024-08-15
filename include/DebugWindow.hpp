#pragma once

#include <string>
#include "Color.hpp"

class Window;

class DebugWindow {
public:
  DebugWindow() = delete;

  static void PrintLine(std::string message);
  static void ActivateColor(Color color);
  static void DeactivateColor(Color color);

  static void SetWindow(Window *window) { DebugWindow::window = window; }

private:
  static Window *window;
};
