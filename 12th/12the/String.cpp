#include "String.h"

String::String(const char* value)
{
    length = value == nullptr ? 1 : static_cast<int>(strlen(value)) + 1;
    data = new char[length];
    if (value != nullptr)
    {
        strcpy_s(data, length, value);
    }
}

String::String(const String& other)
{
    length = other.length;
    data = new char[length];
    strcpy_s(data, length, other.data);
}

String::~String()
{
    delete[] data;
}

String& String::operator=(const String& other)
{
    delete[] data;

    length = other.length;
    data = new char[length];
    strcpy_s(data, length, other.data);

    return *this;
}

String& String::operator+=(const String& other)
{
    length = length + other.length - 1;
    char* newString = new char[length];
    strcpy_s(newString, strlen(data) + 1, data);
    delete[] data;

    strcat_s(newString, length, other.data);
    data = newString;

    return *this;
}

bool String::operator==(const String& other)
{
    return strcmp(data, other.data) == 0;
}

String String::operator+(const String& other)
{
    size_t newLength = length + other.length - 1;
    char* newString = new char[newLength];
    strcpy_s(newString, length, data);
    strcat_s(newString, newLength, other.data);

    String temp = String(newString);
    delete[] newString;
    return temp;
}

std::ostream& operator<<(std::ostream& outStream, const String& other)
{
    outStream << other.data;
    return outStream;
}

std::istream& operator>>(std::istream& inStream, String& other)
{
    char input[255];
    inStream >> input;

    other = String(input);
    return inStream;
}