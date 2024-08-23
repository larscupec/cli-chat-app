#pragma once


class App {
public:
  ~App();

  static App *GetInstance();
  
  void Run(bool isHost, bool isServer);
  void Quit();

  bool GetIsHost() { return isHost; }
  bool GetIsServer() { return isServer; }
  
private:
  App();

  static App *instance;

  bool isHost = false;
  bool isServer = false;
  
  bool isRunning = false;
};
