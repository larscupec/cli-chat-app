#pragma once

#include <string>
#include "Color.hpp"

class Window;

class ConsoleWindow {
public:
  ConsoleWindow() = delete;

  static void PrintLine(std::string message);
  static std::string ReadLine();
  static void ClearLine();
  static void ActivateColor(Color color);
  static void DeactivateColor(Color color);
  
  static Window* GetWindow();

  static void SetWindow(Window *window) { ConsoleWindow::window = window; }

private:
  static Window *window;
};
