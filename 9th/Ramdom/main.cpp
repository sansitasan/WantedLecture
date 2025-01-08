#include <iostream>
#include <stdlib.h>
#include <time.h>

//순수난수 생성기처럼 못하는 이유
//1. 너무 느림 계산량이 많다
//2. 

using namespace std;

int RandomRange(int min, int max) {
	int diff = (max - min) + 1;
	return ((rand() / (RAND_MAX + 1)) * diff) + min;
}

int main() {
	srand(time(nullptr));
	cout << "Random Number: " << rand() << '\n';
	return 0;
}