#pragma once
#include <iostream>

class String
{
public:
    String(const char* value = nullptr);
    String(const String& other);
    ~String();

    String& operator=(const String& other);
    String& operator+=(const String& other);
    bool operator==(const String& other);
    String operator+(const String& other);

    friend std::ostream& operator<<(std::ostream& outStream, const String& other);
    friend std::istream& operator>>(std::istream& inStream, String& other);

private:
    int length;
    char* data;
};

