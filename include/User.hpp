#pragma once

#include <string>

class User
{
public:
  User(std::string username) : username(username) {}
  ~User() {}

  const std::string GetUsername() { return username; }

private:
  std::string username;
};   
