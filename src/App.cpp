#include "App.hpp"
#include "Client.hpp"
#include "ChatWindow.hpp"

#include <ncurses.h>
#include <string>
#include <vector>

App::App()
{
  chatWindow = new ChatWindow();

  chatWindow->client = client;

  // Initialize the ncurses window and show greeting message
  initscr();
  clear();
  keypad(stdscr, TRUE);

  client = new Client(chatWindow);
  client->loadClientInfo();
  
  printw("Hello %s\n", client->username.c_str());

  client->tryAutoConnect();
}

App::~App() {}

void App::run()
{
  isRunning = true;
  
  while (isRunning)
  {
    char commandBuffer[50];

    if (client->getIsConnected()) {

      
    }
  }
}
void processCommand(std::string command, std::vector<std::string> args)
{
  
}
