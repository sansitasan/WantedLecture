#include "PCH.h"
#include "Solution/2473.h"
#include <chrono>

int main() {
	Solution s = Sol2473();

	s.Answer();
	char* arr = new char[100];
	char* arr2 = new char[10000];

	char* arrmove = new char[100];
	char* arrmove2 = new char[10000];
	memset(arrmove, '0', 100);
	memset(arrmove2, '0', 10000);

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memset(arr, 0, sizeof(char) * 100);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "memset 100을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memset(arr2, 0, sizeof(char) * 10000);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "memset 10000을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memmove(arr, arrmove, sizeof(char) * 100);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "memmove 100을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memmove(arr2, arrmove2, sizeof(char) * 10000);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "memmove 10000을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memcpy(arr, arrmove, sizeof(char) * 100);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "memcpy 100을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; ++i) {
		memcpy(arr2, arrmove2, sizeof(char) * 10000);
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "memcpy 10000을 100000번 한 결과: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " microseconds" << '\n';

	delete[] arr;
	delete[] arr2;
	delete[] arrmove;
	delete[] arrmove2;
	return 0;
}