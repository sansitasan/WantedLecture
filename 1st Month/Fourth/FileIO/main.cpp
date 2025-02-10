#include <iostream>

using namespace std;

int main() {
	char buffer[256];
	const char* message = "C 표준 라이브러리 함수로 생성한 텍스트 파일입니다.\n";
	FILE* file = nullptr;

	const type_info& x = typeid(char);

	fopen_s(&file, "text.txt", "w+t");

	if (!file) {
		cout << "file is not exist!!\n";
		return -1;
	}

	fputs(message, file);
	fclose(file);
	fopen_s(&file, "text.txt", "r+t");

	if (!file) {
		cout << "file is not exist!!\n";
		return -1;
	}

	while (true) {
		//두번째 파라미터는 얼마나 읽어올지를 결정한다
		//왜 2 초과여야 할까?
		if (fgets(buffer, 2, file) == nullptr)
		{
			break;
		}

		cout << buffer;
	}

	cin.get();

	fclose(file);
	return 0;
}