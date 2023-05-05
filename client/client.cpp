#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>

#include <ncurses.h>
#include <enet/enet.h>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include "../include/nlohmann/json.hpp"

#include "chatConsole.h"
#include "chatWindow.h"
#include "client.h"

void Client::update()
{
    ENetEvent event;

    while (connected)
    {
        while (enet_host_service(client, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
            {
                nlohmann::json data = nlohmann::json::parse((char*)event.packet->data);

                if (data["type"] == "welcome") {
                    cWin->printMsg(data["message"]);
                }
                else if (data["type"] == "chat") {
                    cWin->printChat(data["username"], data["message"], data["color"]);
                }
                else if (data["type"] == "conversation") {
                    cWin->loadConversation(data);
                }
                break;
            }
            
            case ENET_EVENT_TYPE_DISCONNECT:
                connected = false;
                return;
            }
        }
    }
}

void Client::connect(std::string ip, int port)
{
    ENetEvent event;
    ENetAddress address;

    enet_address_set_host(&address, ip.c_str());
    address.port = port;

    peer = enet_host_connect(client, &address, 2, 0);

    if (peer == NULL)
    {
        fprintf(stderr, "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }

    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        clear();
        refresh();
        printw("Connection to %s:%d succeeded.\n", ip.c_str(), port);
        connected = true;

        // Send client info
        nlohmann::json info;
        info["type"] = "clientInfo";
        info["username"] = username;

        send(info.dump());
    }
    else
    {
        enet_peer_reset(peer);
        printw("Connection to %s:%d failed.\n", ip.c_str(), port);
    }
}

void Client::disconnect()
{
    ENetEvent event;
    enet_peer_disconnect(peer, 0);
    /* Allow up to 3 seconds for the disconnect to succeed
    * and drop any packets received packets.
    */
    while (enet_host_service(client, &event, 3000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            //mvwprintw(scanWin, 2, 0, "Disconnection succeeded.");
            connected = false;
            return;
        }
    }

    // Force disconnect
    enet_peer_reset(peer);
}

void Client::send(std::string msg)
{
    ENetPacket * packet = enet_packet_create(msg.c_str(), strlen(msg.c_str()) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet);
}

void Client::loadClientInfo()
{
    std::ifstream f("clientInfo.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    username = data["username"];
    if (data["autoconnect"] != "no") autoconnectIp = data["autoconnect"];
}

int Client::init()
{
    if (enet_initialize () != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    client = enet_host_create(NULL, 1, 2, 0, 0);

    if (client == NULL)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Client::destroy()
{
    enet_host_destroy(client);
}