#pragma once

#include <ncurses.h>
#include <string>
#include <vector>
#include "Color.hpp"
#include "ChtypeString.hpp"

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
  void Redraw();
  void ActivateColor(Color color);
  void DeactivateColor(Color color);
  void Scroll(int numberOfLines);
  void Resize(int newWidth, int newHeight);
  void Move(int positionX, int positionY);

  bool IsCurrentLineOnScreen();

  int GetCursorPositionX();
  int GetCursorPositionY();
  int GetPadHeight() { return getmaxy(pad); }
  int GetPadWidth() { return getmaxx(pad); }
  WINDOW *GetPad() { return pad; }
  bool GetIsOpen() { return isOpen; }
  std::string GetTitle() { return title; }

  void SetHasFocus(bool state);
  void SetIsOpen(bool state);

private:
  WINDOW *parent = nullptr; // Pointer to the WindowManager's window
  WINDOW *container = nullptr;
  WINDOW *pad = nullptr; // The pad is for writing text

  void DrawBorder();
  void DrawTitle();
  void DrawPad();

  int GetContainerHeight() { return getmaxy(container); }
  int GetContainerWidth() { return getmaxx(container); }
  int GetContainerBeginX() { return getbegx(container); }
  int GetContainerBeginY() { return getbegy(container); }

  std::string title = "";

  bool hasFocus = false;
  bool isOpen = false;

  std::vector<ChtypeString*> lines;
  int firstLineIndex = 0;
  int currentLineIndex = 0;

  Color activeColor = Color::WHITE;
};
