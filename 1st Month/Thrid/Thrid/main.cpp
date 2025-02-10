#include <iostream>

using namespace std;

int main() {
	const char* str = "Hello C++";

	cout << str << '\n';

	size_t len = strlen(str);

	char* heapStr = new char[len + 1];
	strcpy_s(heapStr, len + 1, str);
	//memcpy�� �޸𸮸� �ѹ��� �����ϴ� ���¶� �ε��� ������� �ϳ��ϳ� �����ϴ� �ͺ��� ������
	memcpy(heapStr, str, sizeof(char) * len);
	heapStr[len] = '\0';

	//�������� ������� ������ �޸��ּ�(int)ũ��
	sizeof(heapStr);

	cout << heapStr << '\n';

	delete[] heapStr;

	cin.get();
	return 0;
}