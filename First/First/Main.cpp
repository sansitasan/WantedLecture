//전처리
#include "Main.hpp"

#define Square(x) ((x) * (x))

void Log(const char* message) {
	cout << message << '\n';
}

//진입점
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
	cout << "a, b값을 입력해주세요: " << '\n';
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

	cout << "대문자를 입력해주세요: " << '\n';
	cin >> temp;

	while (temp < 65 || temp > 90) {
		cout << "입력하신 문자는 대문자가 아닙니다. 대문자를 다시 입력해주세요: " << '\n';
		cin >> temp;
	}
	ToLower(temp);
	cout << "입력하신 문자의 소문자는 " << temp << "입니다." << '\n';

	cout << "소문자를 입력해주세요: " << '\n';
	cin >> temp;

	while (temp < 97 || temp > 122) {
		cout << "입력하신 문자는 소문자가 아닙니다. 소문자를 다시 입력해주세요: " << '\n';
		cin >> temp;
	}
	ToUpper(temp);
	cout << "입력하신 문자의 대문자는 " << temp << "입니다." << '\n';
}

void ToLower(char& upperCase) {
	upperCase += 32;
}

void ToUpper(char& lowerCase) {
	lowerCase -= 32;
}

void solutionSix() {
	char str[100];
	cout << "중복을 검사할 문자열을 입력해주세요." << '\n';
	cin.getline(str, 100);

	if (!HasSameCharacter(str, strlen(str))) {
		cout << "문자열 중복 검사 결과는 없음입니다." << '\n';
	}

	else {
		cout << "문자열 중복 검사 결과는 있음입니다." << '\n';
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