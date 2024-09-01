#include "BanList.hpp"
#include "JsonFileReader.hpp"
#include "filesystem"

const std::string BAN_LIST_FILE_PATH = "./banList.json";

BanList::BanList()
{
    if (!std::filesystem::exists(BAN_LIST_FILE_PATH))
    {
        return;
    }

    JsonFileReader banListFile(BAN_LIST_FILE_PATH);
    json banList = banListFile.GetJson();

    for (auto it : banList)
    {
        bannedUsers[it["address"]] = it["username"];
    }
}

json BanList::ToJson()
{
    json result = json::array();

    for (auto addressUsernamePair : bannedUsers)
    {
        json object;
        object["username"] = addressUsernamePair.second;
        object["address"] = addressUsernamePair.first;
        result.push_back(object);
    }

    return result;
}