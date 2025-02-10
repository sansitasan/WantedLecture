#pragma once
#include <iostream>

class Printer {
public:
	inline void ShowString() {
		if (str == nullptr)
			std::cout << "Can't show the string value\n";
		else
			std::cout << str << '\n';
	}

	inline void SetString(const char* newStr) {
		if (newStr == nullptr) return;
		strcpy_s(str, strlen(newStr) + 1, newStr);
	}

	~Printer() {
		delete[] str;
	}

private:
	char* str;
};
