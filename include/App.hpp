#pragma once

class Client;
class Console;

class App {
public:
  App();
  ~App();

  void Run();
  void Quit();
  
private:
  Client *client = nullptr;
  Console *console = nullptr;

  bool isRunning = false;
};
