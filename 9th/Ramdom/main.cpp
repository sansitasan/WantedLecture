#include <iostream>
#include <stdlib.h>
#include <time.h>

//�������� ������ó�� ���ϴ� ����
//1. �ʹ� ���� ��귮�� ����
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