#include "App.hpp"
#include "ChatMode.hpp"
#include "ChatWindow.hpp"
#include "Client.hpp"
#include "CommandMode.hpp"
#include "Console.hpp"
#include "Debug.hpp"
#include "JsonFileReader.hpp"
#include "JsonFileWriter.hpp"
#include <filesystem>
#include <ncursesw/ncurses.h>
#include <string>

const std::string CLIENT_INFO_PATH = "./clientInfo.json";
const std::string DEFAULT_USERNAME = "Guest";

App *App::instance = nullptr;

App *App::GetInstance() {
  if (!instance) {
    instance = new App();
  }
  return instance;
}

App::App() {
  // Read the 'clientInfo.json' file
  // if it does not exist create one

  if (!std::filesystem::exists(CLIENT_INFO_PATH)) {
    Debug::LogWarning("'clientInfo.json' not found, creating a new one...");
    JsonFileWriter clientInfo(CLIENT_INFO_PATH);
    clientInfo.Write("username", DEFAULT_USERNAME);
  }

  Debug::Log("Reading 'clientInfo.json'...");
  JsonFileReader clientInfo(CLIENT_INFO_PATH);
  std::string username = clientInfo.Read<std::string>("username");

  Debug::Log("Initializing the client...");
  Client::GetInstance()->SetUsername(username);

  Debug::Log("Initializing the console...");
  Console::GetInstance()->SetConsoleMode(CommandMode::GetInstance());

  Debug::Log("Done!");
}

void App::Run() {
  Debug::Log("Welcome " + Client::GetInstance()->GetUsername() + "!");

  isRunning = true;

  ChatWindow::PrintLine("Welcome " + Client::GetInstance()->GetUsername() + "!");
  
  while (isRunning) {
    Console::GetInstance()->ProcessInput();
  }
}

void App::Quit() {
  Debug::Log("Exiting clichatapp...");
  isRunning = false;
  if (Client::GetInstance()->GetIsConnected()) {
    Client::GetInstance()->Disconnect();
  }
}
