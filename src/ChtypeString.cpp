#include "ChtypeString.hpp"
#include <stdexcept>

ChtypeString::ChtypeString(const chtype* string)
{
    size_t size = 0;

    while (*string & A_CHARTEXT != '\0')
    {
        size++;

        if (size > MAX_CHTYPE_STRING_SIZE)
        {
            throw std::runtime_error("ChtypeString: string size to big");
        }
    }

    this->size = size;
    this->string = new chtype[size + 1];

    for (size_t i = 0; i < size; i++)
    {
        this->string[i] = string[i];
    }

    this->string[size] = '\0';
}

ChtypeString::ChtypeString(const std::string& string)
{
    this->string = new chtype[string.size() + 1];

    if (!this->string)
    {
        throw std::runtime_error("ChtypeString: couldn't allocate memory for string of size " + string.size());
    }

    for (size_t i = 0; i < string.size(); i++)
    {
        this->string[i] = string[i];
    }
    
    this->string[string.size()] = '\0';
    this->size = string.size();
}

ChtypeString::~ChtypeString()
{
    delete[] string;
}

void ChtypeString::Append(const ChtypeString& string)
{
    size_t newSize = GetSize() + string.GetSize();
    chtype *newString = new chtype[newSize + 1];

    if (!newString)
    {
        throw std::runtime_error("ChtypeString: couldn't allocate memory for string of size " + newSize);
    }

    size_t i;
    for (i = 0; i < GetSize(); i++)
    {
        newString[i] = this->string[i];
    }
    for (size_t j = 0; j < string.GetSize(); j++)
    {
        newString[i] = string[j];
        i++;
    }
    newString[newSize] = '\0';

    delete[] this->string;

    this->string = newString;
    this->size = newSize;
}

void ChtypeString::ApplyColor(const Color color)
{
    for (size_t i = 0; i < size; i++)
    {
        string[i] |= COLOR_PAIR((int)color);
    }
}

void ChtypeString::operator+=(const ChtypeString& other)
{
    Append(other);
}

chtype& ChtypeString::operator[](size_t index) const
{
    if (index > GetSize() - 1 || index < 0)
    {
        throw std::out_of_range("ChtypeString: index was out of range [" + std::to_string(index) + "]");
    }
    return string[index];
}
