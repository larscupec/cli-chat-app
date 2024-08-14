#include "Window.hpp"
#include <algorithm>
#include <cctype>
#include <ncurses/ncurses.h>

std::string TrimString(std::string string) {
  // Trim from start
  string.erase(string.begin(),
               std::find_if(string.begin(), string.end(), [](unsigned char ch) {
                 return !std::isspace(ch);
               }));
  // Trim from end
  string.erase(std::find_if(string.rbegin(), string.rend(),
                            [](unsigned char ch) { return !std::isspace(ch); })
                   .base(),
               string.end());
  return string;
}

Window::Window(WINDOW *parent, std::string title, int height, int width, int positionY,
               int positionX) {
  this->parent = parent;
  this->title = title;
  this->positionX = positionX;
  this->positionY = positionY;
  this->initialHeight = height;
  this->initialWidth = width;

  pad = subpad(parent, height, width, positionY, positionX);

  scrollok(pad, true);
  idlok(pad, true);

  // Draw the border and the title
  // and place the cursor on the first line
  DrawBorder();
  DrawTitle();
  wmove(pad, firstLine, 1);
  
  touchwin(parent);
  prefresh(pad, 0, 0, positionY, positionX, positionY + initialHeight, positionX + initialWidth);

  // Clear the bottom border so it doesn't duplicate when scrolling up
  wmove(pad, GetHeight() - 1, 0);
  wclrtoeol(pad);
  wmove(pad, firstLine, 1);
}

Window::~Window() {
  delwin(pad);
}

void Window::Print(std::string text) {
  waddstr(pad, text.c_str());
  Refresh();
}

void Window::PrintLine(std::string text) {
  // Automatically resize the pad if cursor reached the end
  if (GetCursorPositionY() == GetHeight() - 1) {
    wresize(pad, GetHeight() + 1, GetWidth());
  }
  
  Print(text);
  wmove(pad, GetCursorPositionY() + 1, 1);
  
  Refresh();
}

int Window::GetCursorPositionX() {
  int cursorPositionX, cursorPositionY;
  getyx(pad, cursorPositionY, cursorPositionX);
  return cursorPositionX;
}

int Window::GetCursorPositionY() {
  int cursorPositionX, cursorPositionY;
  getyx(pad, cursorPositionY, cursorPositionX);
  return cursorPositionY;
}

std::string Window::ReadLine() {
  const int BUFFER_SIZE = GetWidth() - 1;
  char buffer[BUFFER_SIZE];
  mvwinnstr(pad, GetCursorPositionY(), 1, buffer, BUFFER_SIZE - 1);
  return TrimString(buffer);
}

void Window::ClearLine() {
  wmove(pad, GetCursorPositionY(), 1);
  wclrtoeol(pad);
  Refresh();
}

void Window::Refresh() {
  touchwin(parent);
  prefresh(pad, padPosition, 1, positionY + 1, positionX + 1, positionY + initialHeight - 2, positionX + initialWidth - 2);
}

void Window::Scroll(int numberOfLines) {
  if (numberOfLines > 0 && padPosition == GetCursorPositionY()) {
    return;
  }
  
  padPosition += numberOfLines;
  
  if (padPosition <= 1) {
    padPosition = 1;
  }
  
  Refresh();

}

void Window::SetHasFocus(bool state) {
  hasFocus = state;

  int currentCursorPositionX = GetCursorPositionX();
  int currentCursorPositionY = GetCursorPositionY();
  
  if (hasFocus) {
    // Highlight the title when focused
    DrawBorder();
    wattron(pad, A_REVERSE);
    DrawTitle();
    wattroff(pad, A_REVERSE);
  }
  else {
    DrawBorder();
    DrawTitle();
  }
  
  wmove(pad, currentCursorPositionY, currentCursorPositionX);
  
  touchwin(parent);
  prefresh(pad, 0, 0, positionY, positionX, positionY, positionX + initialWidth);
}

void Window::DrawTitle() {
  mvwaddstr(pad, 0, 1, this->title.c_str());
}

void Window::DrawBorder() {
  box(pad, 0, 0);
}
