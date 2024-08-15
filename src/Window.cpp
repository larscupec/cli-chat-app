#include "Window.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ncurses/ncurses.h>
#include <string>

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

Window::Window(WINDOW *parent, std::string title, int height, int width,
               int positionY, int positionX) {
  this->parent = parent;
  this->title = title;
  this->positionX = positionX;
  this->positionY = positionY;

  container = subpad(parent, height, width, positionY, positionX);
  pad = subpad(container, height - 2, width - 2, 1, 1);

  scrollok(pad, true);

  DrawBorder();
  DrawTitle();
  wmove(pad, 0, 0);

  Refresh();
}

Window::~Window() {
  delwin(pad);
  delwin(container);
}

void Window::ActivateColor(Color color) {
  wattron(pad, COLOR_PAIR((int)color));
}

void Window::DeactivateColor(Color color) {
  wattroff(pad, COLOR_PAIR((int)color));
}

void Window::Print(std::string text) {
  waddstr(pad, text.c_str());
  Refresh();
}

void Window::PrintLine(std::string text) {
  Print(text);
  waddch(pad, '\n');
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
  const int BUFFER_SIZE = GetPadWidth();
  char buffer[BUFFER_SIZE];
  int ret = mvwinnstr(pad, GetCursorPositionY(), 0, buffer, BUFFER_SIZE - 1);
  return TrimString(buffer);
}

void Window::ClearLine() {
  wmove(pad, GetCursorPositionY(), 0);
  wclrtoeol(pad);
  Refresh();
}

void Window::Refresh() {
  pnoutrefresh(container, 0, 0, positionY, positionX,
               positionY + GetContainerHeight(),
               positionX + GetContainerWidth());

  pnoutrefresh(pad, 0, 0, positionY + 1, positionX + 1,
               positionY + GetPadHeight(), positionX + GetPadWidth());

  doupdate();
}

void Window::DrawTitle() { mvwaddstr(container, 0, 1, this->title.c_str()); }

void Window::DrawBorder() { box(container, 0, 0); }

void Window::Clear() { wclear(pad); }
