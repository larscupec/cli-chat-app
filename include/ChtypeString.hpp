#pragma once

#include <string>
#include <ncurses.h>
#include "Color.hpp"

const size_t MAX_CHTYPE_STRING_SIZE = 2048;

class ChtypeString
{
public:
    ChtypeString(const chtype* string);
    ChtypeString(const std::string& string = "");
    ~ChtypeString();

    void Append(const ChtypeString& string);
    void ApplyColor(const Color color);

    size_t GetSize() const { return size; }
    const chtype *GetString() { return string; }

    void operator+=(const ChtypeString& other);
    chtype& operator[](size_t index) const;

private:
    chtype *string = nullptr;
    size_t size = 0; // Does not account for the null-terminator
};