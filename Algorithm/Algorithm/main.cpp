#include "PCH.h"
#include <string>
#include "Solution/Sol2206.h"
#include <chrono>
#include <windows.h>

void EarlyTestMemInstruct() {
	char* arr = new char[100];
	char* arr2 = new char[10000];

	char* arrmove = new char[100];
	char* arrmove2 = new char[10000];
	memset(arrmove, '0', 100);
	memset(arrmove2, '0', 10000);

	LARGE_INTEGER frequency, start, end;

	// Ÿ�̸� ���ļ� ��������
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memset(arr, 0, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);

	double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memset(arr2, 0, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);

	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memmove(arr, arrmove, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memmove(arr2, arrmove2, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memcpy(arr, arrmove, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memcpy(arr2, arrmove2, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	delete[] arr;
	delete[] arr2;
	delete[] arrmove;
	delete[] arrmove2;
}

void EarlyTestMoveAndCopy() {
	char* arr = new char[100];
	char* arr2 = new char[10000];

	char* arrmove = new char[100];
	char* arrmove2 = new char[10000];
	memset(arrmove, '0', 100);
	memset(arrmove2, '0', 10000);

	LARGE_INTEGER frequency, start, end;

	// Ÿ�̸� ���ļ� ��������
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		for (int j = 0; j < 100; ++j) {
			arr[j] = arrmove[j];
		}
	}
	QueryPerformanceCounter(&end);
	double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		for (int j = 0; j < 100; ++j) {
			arr[j] = std::move(arrmove[j]);
		}
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	delete[] arr;
	delete[] arr2;
	delete[] arrmove;
	delete[] arrmove2;
}

void TestMemInstruct() {
	char* arr = new char[100];
	char* arr2 = new char[10000];

	char* arrmove = new char[100];
	char* arrmove2 = new char[10000];
	memset(arrmove, '0', 100);
	memset(arrmove2, '0', 10000);

	LARGE_INTEGER frequency, start, end;

	// Ÿ�̸� ���ļ� ��������
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memset(arr, 0, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);

	double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;

	std::cout << "memset 100�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memset(arr2, 0, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);

	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "memset 10000�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memmove(arr, arrmove, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "memmove 100�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memmove(arr2, arrmove2, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "memmove 10000�� 10000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memcpy(arr, arrmove, sizeof(char) * 100);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "memcpy 100�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		memcpy(arr2, arrmove2, sizeof(char) * 10000);
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "memcpy 10000�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	delete[] arr;
	delete[] arr2;
	delete[] arrmove;
	delete[] arrmove2;
}

void TestMoveAndCopy() {
	char* arr = new char[100];
	char* arr2 = new char[10000];

	char* arrmove = new char[100];
	char* arrmove2 = new char[10000];
	memset(arrmove, '0', 100);
	memset(arrmove2, '0', 10000);

	LARGE_INTEGER frequency, start, end;

	// Ÿ�̸� ���ļ� ��������
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		for (int j = 0; j < 100; ++j) {
			arr[j] = arrmove[j];
		}
	}
	QueryPerformanceCounter(&end);
	double elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "copy 100�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	QueryPerformanceCounter(&start);
	for (int i = 0; i < 100000; ++i) {
		for (int j = 0; j < 100; ++j) {
			arr[j] = std::move(arrmove[j]);
		}
	}
	QueryPerformanceCounter(&end);
	elapsed = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "move 100�� 100000�� �� ���: "
		<< elapsed
		<< " seconds" << '\n';

	delete[] arr;
	delete[] arr2;
	delete[] arrmove;
	delete[] arrmove2;
}

void Test(int& r) {
	r = NULL;
}

class A {
public:
	virtual void Test() { cout << "Test\n"; }
};

class B : public A {
	//virtual void Test() override { cout << "TestB\n"; }
};

class C : public B
{
	virtual void Test() override { cout << "TestC\n"; }
};

int main() {
	Solution* s = new Sol2206();
	
	s->Answer();
	//SetThreadAffinityMask(GetCurrentThread(), 1);
	//
	//for (int i = 0; i < 10; ++i) {
	//	EarlyTestMemInstruct();
	//}
	//
	//TestMemInstruct();
	//TestMoveAndCopy();
	return 0;
}