#pragma once

#include <map>
#include <string>
#include "Color.hpp"

class UserColorTable {
public:
  UserColorTable() {}

  void Add(std::string username, Color color) { userColors[username] = color; }
  bool HasColor(std::string username) { return userColors.find(username) != userColors.end(); }
  Color GetColor(std::string username) { return userColors[username]; }

private:
  std::map<std::string, Color> userColors;
};
