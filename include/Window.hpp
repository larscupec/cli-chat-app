#pragma once

#include <ncurses/ncurses.h>
#include <string>
#include "Color.hpp"

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

  void ActivateColor(Color color) { wattron(pad, COLOR_PAIR((int)color)); }
  void DeactivateColor(Color color) { wattroff(pad, COLOR_PAIR((int)color)); }

  int GetCursorPositionX();
  int GetCursorPositionY();
  int GetHeight() { return getmaxy(pad); }
  int GetWidth() { return getmaxx(pad); }
  WINDOW *GetPad() { return pad; }

  void SetHasFocus(bool state);

private:
  WINDOW *parent = nullptr; // The pointer to the WindowManager's window
  WINDOW *pad = nullptr; // The pad is for writing text

  void DrawBorder();
  void DrawTitle();

  std::string title = "";

  int initialWidth = 0;
  int initialHeight = 0;

  // Coordinates of the upper-left corner of the pad within the parent window
  int positionX = 0;
  int positionY = 0;

  int firstLine = 1;
  bool hasFocus = false;
  
  int padPosition = 1; // Current line which the pad is displaying
};
