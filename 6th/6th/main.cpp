#include <iostream>
#include <functional>

using namespace std;

function<void()> newFunctionPointer;

template<typename T>
void check(T t) {
	cout << t(10) << '\n';
}

void check2(float (*f)(float)) {
	cout << f(12) << '\n';
}

int main() {
	int a = 17;
	auto func = [&a](float number) { return number + a; };
	//auto test = [a] { ++a; };
	check(func);

	void (*funcPointer)() = []() { };
	return 0;
}