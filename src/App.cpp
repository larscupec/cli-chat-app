#include "App.hpp"
#include <filesystem>
#include <thread>
#include "JsonFileWriter.hpp"
#include "JsonFileReader.hpp"
#include "Client.hpp"
#include "Debug.hpp"

App::App()
{
  const std::string CLIENT_INFO_PATH = "./clientInfo.json";
  const std::string DEFAULT_USERNAME = "Guest";
  
  // Read the 'clientInfo.json' file
  // if it does not exist create one
    
  if (!std::filesystem::exists(CLIENT_INFO_PATH)) {
    Debug::Log("'clientInfo.json' not found, creating a new one...");
    JsonFileWriter clientInfo(CLIENT_INFO_PATH);
    clientInfo.Write("username", DEFAULT_USERNAME);
  }

  Debug::Log("Reading 'clientInfo.json'...");
  JsonFileReader clientInfo(CLIENT_INFO_PATH);
  std::string username = clientInfo.Read<std::string>("username");

  Debug::Log("Initializing the client...");
  client = new Client(username);
}

App::~App()
{
  delete client;
}

void App::Run() {
  while (!client->ConnectTo("localhost", 1234));
  
  std::thread clientThread(&Client::Listen, client);

  clientThread.join();
}
