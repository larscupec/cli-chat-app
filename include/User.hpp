#pragma once

#include "Color.hpp"
#include <string>

class User {
public:
  User(std::string username, Color color) : username(username), color(color) {}
  ~User() {}

  const std::string GetUsername() { return username; }
  const Color GetColor() { return color; }

private:
  std::string username = "";
  Color color = Color::WHITE;
};
