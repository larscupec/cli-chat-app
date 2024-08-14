#pragma once

#include <string>

class User {
public:
  User(std::string username, int color) : username(username), color(color) {}
  ~User() {}

  const std::string GetUsername() { return username; }
  const short GetColor() { return color; }

private:
  std::string username = "";
  int color = 0;
};
