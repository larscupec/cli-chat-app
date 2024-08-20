#pragma once


class App {
public:
  ~App() {}

  static App *GetInstance();
  
  void Run();
  void Quit();
  
private:
  App();

  static App *instance;
  
  bool isRunning = false;
};
