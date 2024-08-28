#include "ConsoleMode.hpp"

bool ConsoleMode::Handle(std::string input) {

  bool result = HandleInput(input);

  if (next && !result) {
    return next->Handle(input);
  }

  return result;
}