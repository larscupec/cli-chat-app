#include "DebugWindow.hpp"
#include "Window.hpp"

Window *DebugWindow::window = nullptr;

void DebugWindow::PrintLine(std::string message) {
  if (!window) {
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
