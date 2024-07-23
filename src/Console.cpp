#include "Console.hpp"
#include <ncurses.h>

Console* Console::instance = nullptr;

Console::Console()
{
  
}

Console::~Console()
{
  
}

Console* Console::getInstance()
{
  if (!instance) {
    instance = new Console();
  }
  return instance;
}    

void Console::moveToOutput()
{
    wmove(scanWindow, 2, 0);
    wclrtoeol(scanWindow);
}

void Console::clearOutput()
{
    moveToOutput();
    wmove(scanWindow, 0, 4);
}

void Console::chatDebug(std::string str)
{
    moveToOutput();
    wprintw(scanWindow, "%s\n", str.c_str());
    wmove(scanWindow, 0, 4);
    wrefresh(scanWindow);
}

void Console::displayPadPosition(int padpos, int rowcount)
{
    int cursorX, cursorY;
    getyx(scanWindow, cursorY, cursorX);
    wmove(scanWindow, 1, 0);
    wclrtoeol(scanWindow);
    wprintw(scanWindow, "padpos: %d, rowcount: %d", padpos, rowcount);
    wmove(scanWindow, cursorY, cursorX);
    wrefresh(scanWindow);
}

void Console::displayCaretPosition(unsigned short caretPosition, unsigned short lastCharIdx)
{
    int cursorX, cursorY;
    getyx(scanWindow, cursorY, cursorX);
    moveToOutput();
    wprintw(scanWindow, "currentCh: %d, lastCh: %d", caretPosition, lastCharIdx);
    wmove(scanWindow, cursorY, cursorX);
    wrefresh(scanWindow);
}
