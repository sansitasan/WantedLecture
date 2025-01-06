#include <iostream>
#include <array>

using namespace std;

template<typename T, size_t size>
class Array {
public:
	T& operator[](int index) {
		if (index > -1 && index < size) {
			return data[index];
		}
		else if (index == -1) {
			return data[size - 1];
		}

		//잘못된 접근
		return data[0];
	}

	size_t Size() const { return size; }

private:
	T data[size];
};

template<typename T, size_t size>
void Func(Array<T, size>& arr) {

}

int main() {

	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int* heapArr = new int[10] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	delete[] heapArr;

	Array<int, 10> myArray;
	myArray[0] = 0;
	myArray[1] = 10;
	myArray[2] = 20;
	myArray[3] = 30;
	myArray[4] = 40;
	myArray[5] = 50;
	myArray[6] = 60;
	myArray[7] = 70;
	myArray[8] = 80;
	myArray[9] = 90;

	array<int, 10> stdArr;
	return 0;
}