#pragma once

#include <ncursesw/ncurses.h>
#include <string>

class Console;

class Window {
public:
  Window(std::string title = "", int height = 0, int width = 0, int positionY = 0, int positionX = 0);
  ~Window();

  friend Console;

  void Refresh() { wrefresh(window); }
  void Clear();

  void Print(std::string text);
  void PrintLine(std::string text);
  std::string ReadLine();
  char ReadKey();

  int GetCursorPositionX();
  int GetCursorPositionY();
  int GetHeight() { return getmaxy(window); }
  int GetWidth() { return getmaxx(window); }

private:
  WINDOW *window = nullptr;

  void DrawBorder();
  void DrawTitle();
  std::string TrimString(std::string string);

  std::string title = "";
  
protected:
  WINDOW *GetWindow() { return window; }
};
