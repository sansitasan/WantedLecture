//��ó��
#include "Main.hpp"

#define Square(x) ((x) * (x))

void Log(const char* message) {
	cout << message << '\n';
}

//������
int main() {
	solutionThree();
	return 0;
}

void solutionOne() {
	int sum = 0;
	for (int i = 1; i < 101; ++i) {
		if (!(i % 2)) sum += i;
	}
	cout << sum << '\n';
}

void solutionTwo() {
	for (int i = 0; i < 5; ++i) {
		for (int j = -1; j < i; ++j) {
			cout << '*';
		}
		cout << '\n';
	}
}

void solutionThree() {
	int a, b;
	cout << "a, b���� �Է����ּ���: " << '\n';
	cin >> a >> b;

	swap(a, b);

	cout << "a: " << a << " b: " << b << '\n';
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void solutionFour() {
	PrintReverse("abcde", 5);
}

void PrintReverse(const char* str, int len) {
	for (int i = len - 1; i >= 0; --i) {
		cout << *(str + sizeof(char) * i);
	}
	cout << '\n';
}

void solutionFive() {
	char temp;

	cout << "�빮�ڸ� �Է����ּ���: " << '\n';
	cin >> temp;

	while (temp < 65 || temp > 90) {
		cout << "�Է��Ͻ� ���ڴ� �빮�ڰ� �ƴմϴ�. �빮�ڸ� �ٽ� �Է����ּ���: " << '\n';
		cin >> temp;
	}
	ToLower(temp);
	cout << "�Է��Ͻ� ������ �ҹ��ڴ� " << temp << "�Դϴ�." << '\n';

	cout << "�ҹ��ڸ� �Է����ּ���: " << '\n';
	cin >> temp;

	while (temp < 97 || temp > 122) {
		cout << "�Է��Ͻ� ���ڴ� �ҹ��ڰ� �ƴմϴ�. �ҹ��ڸ� �ٽ� �Է����ּ���: " << '\n';
		cin >> temp;
	}
	ToUpper(temp);
	cout << "�Է��Ͻ� ������ �빮�ڴ� " << temp << "�Դϴ�." << '\n';
}

void ToLower(char& upperCase) {
	upperCase += 32;
}

void ToUpper(char& lowerCase) {
	lowerCase -= 32;
}

void solutionSix() {
	char str[100];
	cout << "�ߺ��� �˻��� ���ڿ��� �Է����ּ���." << '\n';
	cin.getline(str, 100);

	if (!HasSameCharacter(str, strlen(str))) {
		cout << "���ڿ� �ߺ� �˻� ����� �����Դϴ�." << '\n';
	}

	else {
		cout << "���ڿ� �ߺ� �˻� ����� �����Դϴ�." << '\n';
	}
}

bool HasSameCharacter(const char* testString, int stringLength) {
	unordered_set<char> checkDuplicate;

	for (int i = 0; i < stringLength; ++i) {
		if (checkDuplicate.find(testString[i]) != checkDuplicate.end()) return true;
		checkDuplicate.insert(testString[i]);
	}
	return false;
}