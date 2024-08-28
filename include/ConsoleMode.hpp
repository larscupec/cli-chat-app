#pragma once

#include <string>

class ConsoleMode
{
public:
  virtual ~ConsoleMode() { delete next; }

  virtual bool Handle(std::string input);
  virtual std::string ToString() = 0;

  void SetNext(ConsoleMode *next) { this->next = next; }

private:
  ConsoleMode *next = nullptr;

protected:
  virtual bool HandleInput(std::string input) = 0;
};    
