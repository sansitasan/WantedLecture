#include <iostream>

using namespace std;

void InsertionSort(int* arr, int len) {
	for (int i = 1; i < len; ++i) {
		int keyVal = arr[i];
		int j = i - 1;
		
		while (j >= 0 && arr[j] > keyVal) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = keyVal;
	}
}

void PrintArray(int* arr, int len) {
	for (int i = 0; i < len; ++i) {
		cout << arr[i] << (i < len - 1 ? ", " : "");
	}

	cout << '\n';
}

int main() {

	int arr[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	int len = _countof(arr);

	cout << "정렬 전: ";
	PrintArray(arr, len);

	InsertionSort(arr, len);

	cout << "정렬 후: ";
	PrintArray(arr, len);

	cin.get();
	return 0;
}