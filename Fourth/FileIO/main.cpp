#include <iostream>

using namespace std;

int main() {
	char buffer[256];
	const char* message = "C ǥ�� ���̺귯�� �Լ��� ������ �ؽ�Ʈ �����Դϴ�.\n";
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
		//�ι�° �Ķ���ʹ� �󸶳� �о������ �����Ѵ�
		//�� 2 �ʰ����� �ұ�?
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