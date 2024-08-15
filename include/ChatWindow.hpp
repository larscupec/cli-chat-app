#pragma once

#include <string>
#include "Color.hpp"

class Window;

class ChatWindow {
public:
  ChatWindow() = delete;

  static void PrintLine(std::string message);
  static void Print(std::string message);
  static void ActivateColor(Color color);
  static void DeactivateColor(Color color);

  static void SetWindow(Window *window) { ChatWindow::window = window; }

private:
  static Window *window;
};
