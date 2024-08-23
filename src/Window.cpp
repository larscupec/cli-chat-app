#include "Window.hpp"
#include "StringHelper.hpp"
#include <cctype>
#include <cstdlib>
#include <ncurses/ncurses.h>
#include <string>

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

  lines.push_back("");
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
  if (currentLineIndex >= firstLineIndex &&
      currentLineIndex <= firstLineIndex + GetPadHeight() - 1) {
    waddstr(pad, text.c_str());
    Refresh();
  }
  lines[currentLineIndex] += text;
}

void Window::PrintLine(std::string text) {
  Print(text);
  if (currentLineIndex >= firstLineIndex &&
      currentLineIndex <= firstLineIndex + GetPadHeight() - 1) {

    if (GetCursorPositionY() == GetPadHeight() - 1) {
      firstLineIndex++;
    }
    
    waddch(pad, '\n');
    Refresh();
  }
  lines.push_back("");
  currentLineIndex++;
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
  mvwinnstr(pad, GetCursorPositionY(), 0, buffer, BUFFER_SIZE - 1);
  return StringHelper::TrimString(buffer);
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

void Window::DrawTitle() { mvwaddstr(container, 0, 1, title.c_str()); }

void Window::DrawBorder() { box(container, 0, 0); }

void Window::Clear() { wclear(pad); }

void Window::SetHasFocus(bool state) {
  hasFocus = state;

  if (hasFocus) {
    wattron(container, A_REVERSE);
    DrawTitle();
    wattroff(container, A_REVERSE);
  } else {
    DrawTitle();
  }

  Refresh();
}

void Window::Scroll(int numberOfLines) {
  if (lines.size() < GetPadHeight()) {
    return;
  }

  if (firstLineIndex == 0 && numberOfLines < 0) {
    return;
  }

  if (numberOfLines > 0 &&
      firstLineIndex + GetPadHeight() + numberOfLines > lines.size()) {
    return;
  }

  firstLineIndex += numberOfLines;

  wscrl(pad, numberOfLines);

  int currentCursorPositionX = GetCursorPositionX();
  int currentCursorPositionY = GetCursorPositionY();

  if (numberOfLines < 0) {
    for (int i = 0; i < abs(numberOfLines); i++) {
      mvwaddstr(pad, i, 0, lines[firstLineIndex + i].c_str());
    }
  } else {
    for (int i = 0; i < numberOfLines; i++) {
      mvwaddstr(pad, GetPadHeight() - 1, 0,
                lines[firstLineIndex + GetPadHeight() - 1 - i].c_str());
    }
  }

  wmove(pad, currentCursorPositionY, currentCursorPositionX);

  Refresh();
}
