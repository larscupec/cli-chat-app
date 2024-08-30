#pragma once

#include <string>
#include <map>
#include "json/json.hpp"

using nlohmann::json;

class BanList
{
public:
    BanList();
    ~BanList() {}

    void Add(unsigned int address, std::string username) { bannedUsers[address] = username; }
    void Remove(unsigned int address) { bannedUsers.erase(address); }
    bool Exists(unsigned int address) { return bannedUsers.find(address) != bannedUsers.end(); }
    json ToJson();
    std::string GetUsername(unsigned int address) { return bannedUsers[address]; }

private:
    std::map<unsigned int, std::string> bannedUsers;
};