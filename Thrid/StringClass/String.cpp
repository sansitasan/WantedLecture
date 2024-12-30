#include "String.h"

String::String()
	:String(nullptr) {}

String::String(const char* string)
{
	length = string == nullptr ? 0 : static_cast<int>(strlen(string));
	data = new char[length + 1];
	if (string != nullptr) {
		strcpy_s(data, length + 1, string);
	}
}

String::String(const String& other)
{
	length = other.length;
	data = new char[length + 1];
	strcpy_s(data, length + 1, other.data);
}

String::~String()
{
	if (data) {
		delete[] data;
	}
}

String& String::operator=(const String& other)
{
	delete[] data;

	length = other.length;
	data = new char[length + 1];
	strcpy_s(data, length + 1, other.data);

	return *this;
}

String String::operator+(const String& other)
{
	size_t len = length + other.length + 1;
	char* newStr = new char[len];
	strcpy_s(newStr, length + 1, data);
	memcpy(newStr + length, other.data, len - length);
	String ret(newStr);
	delete[] newStr;

	return ret;
}

bool String::operator==(const String& other)
{
	return !strcmp(data, other.data);
}

bool String::operator!=(const String& other)
{
	return strcmp(data, other.data);
}
