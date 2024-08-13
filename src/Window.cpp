#include "Window.hpp"
#include <algorithm>
#include <cctype>

Window::Window(std::string title, int height, int width, int positionY,
               int positionX) {
  this->title = title;

  window = newwin(height, width, positionY, positionX);

  DrawBorder();
  DrawTitle();
  wmove(window, 1, 1);

  Refresh();
}

Window::~Window() { delwin(window); }

void Window::Print(std::string text) {
  waddstr(window, text.c_str());
  Refresh();
}

void Window::PrintLine(std::string text) {
  Print(text);
  wmove(window, GetCursorPositionY() + 1, 1);
  Refresh();
}

int Window::GetCursorPositionX() {
  int cursorPositionX, cursorPositionY;
  getyx(window, cursorPositionY, cursorPositionX);
  return cursorPositionX;
}

int Window::GetCursorPositionY() {
  int cursorPositionX, cursorPositionY;
  getyx(window, cursorPositionY, cursorPositionX);
  return cursorPositionY;
}

std::string Window::ReadLine() {
  const int BUFFER_SIZE = 500;
  char buffer[BUFFER_SIZE];
  mvwinnstr(window, GetCursorPositionY(), 1, buffer, BUFFER_SIZE - 1);
  return TrimString(buffer);
}

void Window::Clear() {
  wclear(window);

  DrawBorder();
  DrawTitle();

  wmove(window, 1, 1);
}

void Window::DrawBorder() {
  box(window, 0, 0);
  Refresh();
}

void Window::DrawTitle() {
  mvwaddstr(window, 0, 1, this->title.c_str());
  Refresh();
}

char Window::ReadKey() { return wgetch(window); }

std::string Window::TrimString(std::string string) {
  // Trim from start
  string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
  //Trim from end
  string.erase(std::find_if(string.rbegin(), string.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), string.end());
  return string;
}
