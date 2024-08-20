#include "ChatWindow.hpp"
#include "Window.hpp"

Window *ChatWindow::window = nullptr;

void ChatWindow::PrintLine(std::string message) {
  if (!window) {
    return;
  }
  window->PrintLine(message);
}

void ChatWindow::Print(std::string message) {
  if (!window) {
    return;
  }
  window->Print(message);
}

void ChatWindow::ActivateColor(Color color) {
  if (!window) {
    return;
  }
  window->ActivateColor(color);
}

void ChatWindow::DeactivateColor(Color color) {
  if (!window) {
    return;
  }
  window->DeactivateColor(color);
}

void ChatWindow::Clear() {
  if (!window) {
    return;
  }
  window->Clear();
}
