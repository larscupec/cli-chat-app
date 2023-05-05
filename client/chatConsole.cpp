#include "chatConsole.h"

#include <ncurses.h>

void ChatConsole::moveToOutput()
{
    wmove(scanWin, 2, 0);
    wclrtoeol(scanWin);
}

void ChatConsole::clearCommandOutput()
{
    moveToOutput();
    wmove(scanWin, 0, 4);
}

void ChatConsole::chatDebug(std::string str)
{
    moveToOutput();
    wprintw(scanWin, "%s\n", str.c_str());
    wmove(scanWin, 0, 4);
    wrefresh(scanWin);
}

void ChatConsole::debugPadPosition(int padpos, int rowcount)
{
    int cursorX, cursorY;
    getyx(scanWin, cursorY, cursorX);
    wmove(scanWin, 1, 0);
    wclrtoeol(scanWin);
    wprintw(scanWin, "padpos: %d, rowcount: %d", padpos, rowcount);
    wmove(scanWin, cursorY, cursorX);
    wrefresh(scanWin);
}

void ChatConsole::debugCaretPosition(unsigned short caretPosition, unsigned short lastCharIdx)
{
    int cursorX, cursorY;
    getyx(scanWin, cursorY, cursorX);
    moveToOutput();
    wprintw(scanWin, "currentCh: %d, lastCh: %d", caretPosition, lastCharIdx);
    wmove(scanWin, cursorY, cursorX);
    wrefresh(scanWin);
}