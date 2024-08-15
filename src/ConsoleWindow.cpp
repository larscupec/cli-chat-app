#include "ConsoleWindow.hpp"
#include "Window.hpp"

Window *ConsoleWindow::window = nullptr;

void ConsoleWindow::PrintLine(std::string message) {
  if (!window) {
    return;
  }
  window->PrintLine(message);
}

void ConsoleWindow::ActivateColor(Color color) {
  if (!window) {
    return;
  }
  window->ActivateColor(color);
}

void ConsoleWindow::DeactivateColor(Color color) {
  if (!window) {
    return;
  }
  window->DeactivateColor(color);
}

std::string ConsoleWindow::ReadLine() {
  if (!window) {
    return "";
  }
  return window->ReadLine();
}

void ConsoleWindow::ClearLine() {
  if (!window) {
    return;
  }
  window->ClearLine();
}

Window *ConsoleWindow::GetWindow() {
  return window;
}
