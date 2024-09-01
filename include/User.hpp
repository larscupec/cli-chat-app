#pragma once

#include "Color.hpp"
#include <string>
#include <ctime>

class User
{
public:
  User(std::string username, Color color) : username(username), color(color) {}
  ~User() {}

  const std::string GetUsername() { return username; }
  const Color GetColor() { return color; }
  bool IsMuted() { return lastMuteTime + muteTimeSec > time(nullptr); }
  void Mute(unsigned int seconds) { muteTimeSec = seconds; lastMuteTime = time(nullptr); }
  void Unmute() { muteTimeSec = 0; }

private:
  std::string username = "";
  Color color = Color::WHITE;
  time_t lastMuteTime = 0;
  unsigned int muteTimeSec = 0;
};
