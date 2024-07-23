#pragma once

#include <string>

class User
{
public:
    User() {};
    ~User() {};

    unsigned short id;
    std::string username;
    unsigned char color;
};
