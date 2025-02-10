#include <iostream>

using namespace std;

int main() {
	const char* str = "Hello C++";

	cout << str << '\n';

	size_t len = strlen(str);

	char* heapStr = new char[len + 1];
	strcpy_s(heapStr, len + 1, str);
	//memcpy는 메모리를 한번에 복사하는 형태라 인덱스 기반으로 하나하나 복사하는 것보다 빠르다
	memcpy(heapStr, str, sizeof(char) * len);
	heapStr[len] = '\0';

	//포인터의 사이즈는 언제나 메모리주소(int)크기
	sizeof(heapStr);

	cout << heapStr << '\n';

	delete[] heapStr;

	cin.get();
	return 0;
}