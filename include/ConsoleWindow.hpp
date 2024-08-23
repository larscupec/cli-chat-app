#pragma once

#include <string>
#include "Color.hpp"

class Window;

class ConsoleWindow {
public:
  ConsoleWindow() = delete;

  static void PrintLine(std::string message);
  static std::string ReadLine();
  static void Clear();
  static void ActivateColor(Color color);
  static void DeactivateColor(Color color);
  
  static Window* GetWindow() { return window; }

  static void SetWindow(Window *window) { ConsoleWindow::window = window; }

private:
  static Window *window;
};
