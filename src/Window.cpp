#include "Window.hpp"
#include "StringHelper.hpp"
#include <cctype>
#include <cstdlib>
#include <ncurses/ncurses.h>
#include <string>
#include <cmath>

Window::Window(WINDOW *parent, std::string title, int height, int width,
               int positionY, int positionX)
{
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

Window::~Window()
{
  delwin(pad);
  delwin(container);
}

void Window::ActivateColor(Color color)
{
  wattron(pad, COLOR_PAIR((int)color));
}

void Window::DeactivateColor(Color color)
{
  wattroff(pad, COLOR_PAIR((int)color));
}

void Window::Print(std::string text)
{
  size_t neededNumberOfLines = ceil(text.size() / (double)GetPadWidth());

  size_t startPos = 0;
  for (size_t i = 0; i < neededNumberOfLines; i++)
  {
    if (i > 0)
    {
      lines.push_back("");
      currentLineIndex++;
    }

    std::string line = text.substr(startPos, GetPadWidth());
    lines[currentLineIndex] += line;
    startPos += line.size();

    if (IsCurrentLineOnScreen())
    {
      if (GetCursorPositionY() == GetPadHeight() - 1 && (line.back() == '\n' || line.size() == GetPadWidth()))
      {
        firstLineIndex++;
      }
      waddstr(pad, line.c_str());
    }
  }

  Refresh();
}

void Window::PrintLine(std::string text)
{
  Print(text + "\n");

  lines.push_back("");
  currentLineIndex++;
}

int Window::GetCursorPositionX()
{
  int cursorPositionX, cursorPositionY;
  getyx(pad, cursorPositionY, cursorPositionX);
  return cursorPositionX;
}

int Window::GetCursorPositionY()
{
  int cursorPositionX, cursorPositionY;
  getyx(pad, cursorPositionY, cursorPositionX);
  return cursorPositionY;
}

std::string Window::ReadLine()
{
  const int BUFFER_SIZE = GetPadWidth();
  char buffer[BUFFER_SIZE];
  mvwinnstr(pad, GetCursorPositionY(), 0, buffer, BUFFER_SIZE - 1);
  return StringHelper::TrimString(buffer);
}

void Window::Refresh()
{
  pnoutrefresh(container, 0, 0, positionY, positionX,
               positionY + GetContainerHeight(),
               positionX + GetContainerWidth());

  pnoutrefresh(pad, 0, 0, positionY + 1, positionX + 1,
               positionY + GetPadHeight(), positionX + GetPadWidth());

  doupdate();
}

void Window::DrawTitle() { mvwaddstr(container, 0, 1, title.c_str()); }

void Window::DrawBorder() { box(container, 0, 0); }

void Window::Clear()
{
  lines.clear();
  lines.push_back("");
  firstLineIndex = 0;
  currentLineIndex = 0;
  wclear(pad);
  Refresh();
}

void Window::SetHasFocus(bool state)
{
  hasFocus = state;

  if (hasFocus)
  {
    wattron(container, A_REVERSE);
    DrawTitle();
    wattroff(container, A_REVERSE);
  }
  else
  {
    DrawTitle();
  }

  Refresh();
}

// This is evil!
void Window::Scroll(int numberOfLines)
{
  if (numberOfLines == 0)
  {
    return;
  }

  firstLineIndex += numberOfLines;

  wclear(pad);
  wmove(pad, 0, 0);

  for (int i = firstLineIndex; i < std::min(firstLineIndex + GetPadHeight(), (int)lines.size()); i++)
  {
    if (i < 0)
    {
      waddstr(pad, "~\n");
    }
    else
    {
      waddstr(pad, lines[i].c_str());
    }
  }

  Refresh();
}

bool Window::IsCurrentLineOnScreen()
{
  return currentLineIndex >= firstLineIndex &&
         currentLineIndex <= firstLineIndex + GetPadHeight() - 1;
}