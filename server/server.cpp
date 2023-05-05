#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <thread>

#include <enet/enet.h>
#include "../include/nlohmann/json.hpp"

static bool running = false;

static int connectedUsers = 0;
static int lastFreeId = 0;

class User
{
public:
    User() {};
    ~User() {};

    unsigned short id;
    std::string username;
    unsigned char color;
};

std::vector<User*> users;

std::map<short, int> colorMap;

nlohmann::ordered_json conversation;

User* addNewUser()
{
    User* newUser = new User();
    newUser->id = lastFreeId;
    newUser->username = "User" + std::to_string(lastFreeId);
    users.push_back(newUser);
    lastFreeId++;

    // Give the user their color
    short colorId;
    do {
        colorId = 1 + rand() % 33;
    } while (colorMap[colorId] != -1);
    
    colorMap[colorId] = newUser->id;
    newUser->color = colorId;

    return users.back();
}

void removeUser(User* user)
{
    for (size_t i = 0; i < users.size(); i++)
    {
        if (user == users[i]) {
            delete user;
            users[i] = users[users.size() - 1];
            users.pop_back();

            // Free the color
            for (size_t j = 1; j <= 32; j++) {
                if (colorMap[i] == j)
                    colorMap[i] = -1;
            }
        }
    }
}

void consoleInput()
{
    std::string command;

    while (true)
    {
        std::getline(std::cin, command);

        if (command == "stop") {
            puts("Stopping server...");
            running = false;
            break;
        }
        else if (command == "printconv") {
            puts(conversation.dump().c_str());
        }
        else {
            puts("Unknown command.");
        }
    }
}

void makeColorMap()
{
    for (size_t i = 1; i <= 32; i++)
    {
        // Set all colors to belong to no one
        colorMap[i] = -1;
    }
}

int main()
{
    if (enet_initialize () != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetHost* server;
    ENetAddress address;

    std::ifstream sf("settings.json");
    nlohmann::json settings = nlohmann::json::parse(sf);
    sf.close();

    address.host = ENET_HOST_ANY;
    address.port = settings["port"];

    server = enet_host_create(&address, 32, 2, 0, 0);

    if (server == NULL)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }

    running = true;

    printf("Server started on port %d\n", address.port);

    std::thread t1(consoleInput);

    srand(time(nullptr));
    makeColorMap();

    // JSON object for stroing conversation
    std::ifstream f("conversation.json");
    if (f.good()) {
        conversation = nlohmann::json::parse(f);
    }
    else {
        conversation = nlohmann::json::array();
    }
    f.close();

    ENetEvent event;

    // Main server loop
    while (running)
    {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 1000) > 0)
        {
            User* user = static_cast<User*>(event.peer->data);

            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
            {
                printf("A new client connected from %x:%u.\n", 
                        event.peer->address.host,
                        event.peer->address.port);

                event.peer->data = addNewUser();

                // Send the conversation to the new client
                nlohmann::json j;
                j["type"] = "conversation";
                j["conversation"] = conversation;
                std::string conv = j.dump();

                ENetPacket* packet = enet_packet_create(conv.c_str(), strlen(conv.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(event.peer, 0, packet);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE:
            {
                nlohmann::json data = nlohmann::json::parse((char*)event.packet->data);

                printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                        (unsigned int)event.packet->dataLength,
                        (char*)event.packet->data,
                        user->username.c_str(),
                        (unsigned int)event.channelID);

                if (data["type"] == "clientInfo") {
                    user->username = data["username"];

                    nlohmann::json msg;
                    msg["type"] = "welcome";
                    msg["message"] = user->username + " joined the server.";
                    std::string msgPacket = msg.dump();

                    // Store the message in conversation
                    conversation.push_back(msgPacket);

                    // Send welcome message
                    ENetPacket* packet = enet_packet_create(msgPacket.c_str(), strlen(msgPacket.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(server, 0, packet);
                }
                else if (data["type"] == "chatMessage") {
                    // Format message
                    std::string msg = user->username + ": ";
                    msg.append(data["content"]);
                    printf("%s\n", msg.c_str());

                    nlohmann::json j;
                    j["type"] = "chat";
                    j["username"] = user->username;
                    j["message"] = data["content"];
                    j["color"] = (short)user->color;
                    std::string msgPacket = j.dump();

                    // Store the message in conversation
                    conversation.push_back(msgPacket);

                    // Send message
                    ENetPacket* packet = enet_packet_create(msgPacket.c_str(), strlen(msgPacket.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
                    enet_host_broadcast(server, 0, packet);
                }

                enet_packet_destroy(event.packet);
                
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
            {
                printf("%s disconnected.\n", user->username.c_str());

                nlohmann::json msg;
                msg["type"] = "welcome";
                msg["message"] = user->username + " left the server.";
                std::string msgPacket = msg.dump();

                // Store the message in conversation
                conversation.push_back(msgPacket);

                // Send disconnect message
                ENetPacket* packet = enet_packet_create(msgPacket.c_str(), strlen(msgPacket.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
                enet_host_broadcast(server, 0, packet);

                removeUser(user);
                event.peer->data = NULL;
            }
            }
        }
    }

    t1.join();

    enet_host_destroy(server);

    // Save conversation
    std::ofstream o("conversation.json");
    o << conversation;
    o.close();

    // Free users
    for (auto user : users)
    {
        delete user;
    }
    
    return 0;
}