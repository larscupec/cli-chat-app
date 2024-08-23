#include "App.hpp"
#include "ChatMode.hpp"
#include "ChatWindow.hpp"
#include "Client.hpp"
#include "ClientCommandMode.hpp"
#include "Console.hpp"
#include "ConsoleWindow.hpp"
#include "Debug.hpp"
#include "DebugWindow.hpp"
#include "JsonFileReader.hpp"
#include "JsonFileWriter.hpp"
#include "Server.hpp"
#include "ServerCommandMode.hpp"
#include "ThreadManager.hpp"
#include "Window.hpp"
#include "WindowManager.hpp"
#include <filesystem>
#include <ncursesw/ncurses.h>
#include <string>
#include <thread>

const std::string CLIENT_INFO_PATH = "./clientInfo.json";
const std::string DEFAULT_USERNAME = "Guest";
const int CONSOLE_HEIGHT = 3;
const int DEFAULT_SERVER_PORT = 1234;

App *App::instance = nullptr;

App *App::GetInstance() {
  if (!instance) {
    instance = new App();
  }
  return instance;
}

App::App() {

  Debug::Log("Initializing the console...");

  Debug::Log("Done!");
}

void App::Run(bool isHost, bool isServer) {
  this->isHost = isHost;
  this->isServer = isServer;
  
  Debug::Log("Starting clichatapp...");

  Debug::Log("Creating NCurses windows...");

  int maxWidth = getmaxx(stdscr);
  int maxHeight = getmaxy(stdscr);

  WINDOW *mainWindow = newpad(maxHeight, maxWidth);

  if (!isServer) {

    Window *chatWindow = new Window(mainWindow, "Chat",
                                    maxHeight - CONSOLE_HEIGHT, maxWidth / 2);
    Window *debugWindow =
        new Window(mainWindow, "Debug", maxHeight - CONSOLE_HEIGHT,
                   maxWidth / 2, 0, maxWidth / 2);
    Window *consoleWindow = new Window(mainWindow, "Console", CONSOLE_HEIGHT,
                                       maxWidth, maxHeight - CONSOLE_HEIGHT, 0);

    ChatWindow::SetWindow(chatWindow);
    DebugWindow::SetWindow(debugWindow);
    ConsoleWindow::SetWindow(consoleWindow);

    WindowManager::Add(chatWindow);
    WindowManager::Add(debugWindow);
    WindowManager::Add(consoleWindow);

    chatWindow->SetHasFocus(true);

    if (!std::filesystem::exists(CLIENT_INFO_PATH)) {
      Debug::LogWarning(
          "'clientInfo.json' was not found, creating a new one...");
      JsonFileWriter clientInfo(CLIENT_INFO_PATH);
      clientInfo.Write("username", DEFAULT_USERNAME);
    }

    Debug::Log("Reading 'clientInfo.json'...");
    JsonFileReader clientInfo(CLIENT_INFO_PATH);
    std::string username = clientInfo.Read<std::string>("username");

    Debug::Log("Initializing the client...");
    Client::GetInstance()->SetUsername(username);

    Console::GetInstance()->SetConsoleMode(ClientCommandMode::GetInstance());

    Debug::Log("Done!");

    Debug::Log("Welcome " + Client::GetInstance()->GetUsername() + "!");
    ChatWindow::PrintLine("Welcome " + Client::GetInstance()->GetUsername() +
                          "!");

    if (isHost) {
      std::thread *serverThread =
          new std::thread(&Server::Start, Server::GetInstance(), DEFAULT_SERVER_PORT);
      ThreadManager::Add(serverThread);
    }
  } else {
    Window *debugWindow =
        new Window(mainWindow, "Debug", maxHeight - CONSOLE_HEIGHT, maxWidth);
    Window *consoleWindow = new Window(mainWindow, "Console", CONSOLE_HEIGHT,
                                       maxWidth, maxHeight - CONSOLE_HEIGHT, 0);

    DebugWindow::SetWindow(debugWindow);
    ConsoleWindow::SetWindow(consoleWindow);

    WindowManager::Add(debugWindow);
    WindowManager::Add(consoleWindow);

    debugWindow->SetHasFocus(true);

    std::thread *serverThread =
        new std::thread(&Server::Start, Server::GetInstance(), DEFAULT_SERVER_PORT);
    ThreadManager::Add(serverThread);

    Console::GetInstance()->SetConsoleMode(ServerCommandMode::GetInstance());
  }

  isRunning = true;

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
  if (Server::GetInstance()->GetIsRunning()) {
    Server::GetInstance()->Stop();
  }
}

App::~App() {
  delete ChatWindow::GetWindow();
  delete DebugWindow::GetWindow();
  delete ConsoleWindow::GetWindow();
}
