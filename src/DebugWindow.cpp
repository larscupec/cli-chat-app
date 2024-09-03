#include "DebugWindow.hpp"
#include "Window.hpp"
#include <iostream>

Window *DebugWindow::window = nullptr;

void DebugWindow::PrintLine(std::string message) {
  if (!window) {
    std::cout << message << std::endl;
    return;
  }
  window->PrintLine(message);
}

void DebugWindow::ActivateColor(Color color) {
  if (!window) {
    return;
  }
  window->ActivateColor(color);
}

void DebugWindow::DeactivateColor(Color color) {
  if (!window) {
    return;
  }
  window->DeactivateColor(color);
}
