#pragma once

class Client;

class App
{
public:
  App();
  ~App();

  void Run();

private:
  Client *client = nullptr;
};   
