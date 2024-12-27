#pragma once
#include <iostream>

class String
{
public:
	String();

	String(const char* string);
	String(const String& other);
	~String();

	String& operator=(const String& other);

	String operator+(const String& other);

	bool operator==(const String& other);

	bool operator!=(const String& other);

	friend std::ostream& operator<<(std::ostream& os, const String& string) {
		os << string.data;
		return os;
	}

	inline const int Length() const {
		return length;
	}

	inline const char* Data() const {
		return data;
	}

private:
	char* data;
	int length;
};

