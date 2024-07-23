#pragma once

#include <string>

typedef struct _win_st WINDOW;

class Console {
private:
  Console();

  static Console *instance;
  WINDOW *scanWindow = nullptr;

public:
  Console(const Console& obj) = delete;
  ~Console();

  static Console* getInstance();
  void setScanWindow(WINDOW *scanWindow) { this->scanWindow = scanWindow; }
  
  void moveToOutput();
  void clearOutput();
  void chatDebug(std::string);
  void displayPadPosition(int, int);
  void displayCaretPosition(unsigned short, unsigned short);
};
