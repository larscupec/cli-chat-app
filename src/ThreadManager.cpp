#include "ThreadManager.hpp"

std::vector<std::thread *> ThreadManager::threads;

void ThreadManager::JoinAll() {
  for (auto& thread : threads) {
    thread->join();
    delete thread;
  }
  threads.clear();
}
