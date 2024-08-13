#pragma once

#include <thread>
#include <vector>

class ThreadManager {
public:
  ThreadManager() {}
  ~ThreadManager() {}

  static void Add(std::thread *thread) { threads.push_back(thread); }
  
  static void JoinAll();
  
private:
  static std::vector<std::thread*> threads;
};
