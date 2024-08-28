#include "WindowManager.hpp"
#include "ChatWindow.hpp"
#include "ConsoleWindow.hpp"
#include "DebugWindow.hpp"
#include "Window.hpp"
#include "Debug.hpp"
#include <vector>

std::vector<Window *> WindowManager::windows;
int WindowManager::focusedWindowIndex = 0;

void WindowManager::FocusNextWindow()
{
  windows[focusedWindowIndex]->SetHasFocus(false);

  do
  {
    focusedWindowIndex++;
    if (focusedWindowIndex == windows.size())
    {
      focusedWindowIndex = 0;
    }
  } while (!windows[focusedWindowIndex]->GetIsOpen());

  windows[focusedWindowIndex]->SetHasFocus(true);
}

void WindowManager::CloseFocusedWindow()
{
  if (GetFocusedWindow() == ConsoleWindow::GetWindow())
  {
    return;
  }

  GetFocusedWindow()->SetIsOpen(false);

  if (IsOnlyConsoleOpen())
  {
    Focus(ConsoleWindow::GetWindow());
    return;
  }

  FocusNextNotConsole();
  Maximize(GetFocusedWindow());
}

void WindowManager::OpenWindow(std::string windowTitle)
{
  Window *window = Find(windowTitle);

  if (!window || window == ConsoleWindow::GetWindow() || window->GetIsOpen())
  {
    return;
  }

  if (IsOnlyConsoleOpen())
  {
    Window *window = Find(windowTitle);
    Maximize(window);
    window->SetIsOpen(true);
    Focus(window);
  }
  else
  {
    SplitToLeft(window);
    FocusNextNotConsole();
    SplitToRight(GetFocusedWindow());
    window->SetIsOpen(true);
    Focus(window);
  }
}

void WindowManager::FocusNextNotConsole()
{
  do
  {
    FocusNextWindow();
  } while (GetFocusedWindow() == ConsoleWindow::GetWindow());
}

Window *WindowManager::Find(std::string windowTitle)
{
  for (Window *window : windows)
  {
    if (window->GetTitle() == windowTitle)
    {
      return window;
    }
  }
  return nullptr;
}

void WindowManager::Focus(Window *window)
{
  GetFocusedWindow()->SetHasFocus(false);
  window->SetHasFocus(true);
  for (size_t i = 0; i < windows.size(); i++)
  {
    if (windows[i] == window)
    {
      focusedWindowIndex = i;
      return;
    }
  }
}

bool WindowManager::IsOnlyConsoleOpen()
{
  Window *openWindow = nullptr;
  int openWindowsCount = 0;

  for (Window *window : windows)
  {
    if (window->GetIsOpen())
    {
      openWindowsCount++;
      openWindow = window;
    }
  }

  if (openWindowsCount == 1 && openWindow == ConsoleWindow::GetWindow())
  {
    return true;
  }

  return false;
}

void WindowManager::Maximize(Window *window)
{
  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  window->Move(0, 0);
  window->Resize(maxWidth, maxHeight - CONSOLE_HEIGHT);
}

void WindowManager::SplitToRight(Window *window)
{
  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  window->Resize(maxWidth / 2, maxHeight - CONSOLE_HEIGHT);
  window->Move(maxWidth / 2, 0);
}

void WindowManager::SplitToLeft(Window *window)
{
  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  window->Move(0, 0);
  window->Resize(maxWidth / 2, maxHeight - CONSOLE_HEIGHT);
}
