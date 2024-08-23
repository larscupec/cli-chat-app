#pragma once

#include <ncurses/ncurses.h>
#include <string>
#include <vector>
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
  void Clear();

  void ActivateColor(Color color);
  void DeactivateColor(Color color);

  void Scroll(int numberOfLines);

  int GetCursorPositionX();
  int GetCursorPositionY();
  int GetPadHeight() { return getmaxy(pad); }
  int GetPadWidth() { return getmaxx(pad); }
  WINDOW *GetPad() { return pad; }

  void SetHasFocus(bool state);

private:
  WINDOW *parent = nullptr; // Pointer to the WindowManager's window
  WINDOW *container = nullptr;
  WINDOW *pad = nullptr; // The pad is for writing text

  void DrawBorder();
  void DrawTitle();

  int GetContainerHeight() { return getmaxy(container); }
  int GetContainerWidth() { return getmaxx(container); }

  std::string title = "";

  bool hasFocus = false;

  // Coordinates of the upper-left corner of the container within the parent window
  int positionX = 0;
  int positionY = 0;

  std::vector<std::string> lines;
  int firstLineIndex = 0;
  int currentLineIndex = 0;
};
