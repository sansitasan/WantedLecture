#include <iostream>

using namespace std;

template<typename T>
void Swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

int main() {
	float a = 3.5f, b = 4.5f;

	Swap(a, b);

	cout << a << '\t' << b;

	cin.get();

	return 0;
}