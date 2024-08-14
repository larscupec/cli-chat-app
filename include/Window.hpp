#pragma once

#include <ncursesw/ncurses.h>
#include <string>

class Window {
public:
  Window(WINDOW *parent, std::string title = "", int height = 0, int width = 0,
         int positionY = 0, int positionX = 0);
  ~Window();

  void Refresh();

  void Print(std::string text);
  void PrintLine(std::string text);
  std::string ReadLine();
  void ClearLine();

  void Scroll(int numberOfLines);

  int GetCursorPositionX();
  int GetCursorPositionY();
  int GetHeight() { return getmaxy(pad); }
  int GetWidth() { return getmaxx(pad); }
  WINDOW *GetPad() { return pad; }

  void SetHasFocus(bool state);

private:
  WINDOW *parent = nullptr; // The pointer to the WindowManager's window
  WINDOW *pad = nullptr; // The pad is for writing text

  std::string TrimString(std::string string);
  void DrawTitle();

  std::string title = "";

  // Coordinates of the upper-left corner of the pad within the parent window
  int positionX = 0;
  int positionY = 0;

  int firstLine = 1;
  bool hasFocus = false;
  
  int padPosition = 1; // Current line which the pad is displaying
};
