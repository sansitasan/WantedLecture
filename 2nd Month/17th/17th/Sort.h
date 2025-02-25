#pragma once
#include <iostream>

using namespace std;

class ISort {
public:
	virtual void Sort(int* arr, int len, int start = 0) = 0;
	void Print(int* arr, int len) {
		for (int i = 0; i < len; ++i) {
			cout << arr[i] << (i < len - 1 ? ", " : "");
		}

		cout << '\n';
	}
	virtual ~ISort() {}
};

class InsertSort : public ISort{
public:
	virtual void Sort(int* arr, int len, int start = 0) override {
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
};

class QuickSort : public ISort {
	//퀵정렬 피벗 고르는 방법이 중요
	//랜덤 = 무작위 값 선택 -> 최악의 경우를 큰 확률로 피한다.
	//처음 데이터 집합의 세 요소(혹은 그 이상) 중 중간 값을 기준으로 -> 최악의 경우를 항상 피한다.
	//퀵정렬 주의사항
	//파티션 크기가 16 이하에 쓰면 문제가 생긴다.
	//OutOfIndex문제가 발생할 수 있다.
public:
	virtual void Sort(int* arr, int len, int start = 0) override {
		QSort(arr, start, len);
	}

private:
	void QSort(int* arr, int left, int right) {
		if (left >= right) return;

		int partiotion = Partition(arr, left, right);
		QSort(arr, left, partiotion - 1);
		QSort(arr, partiotion + 1, right);
	}

	int Partition(int* arr, int left, int right) {
		//피벗 선택
		int first = left;
		int pivot = arr[first];
		//피벗 이후부터 비교
		++left;

		while (left <= right) {
			while (left <= right && arr[left] <= pivot) {
				++left;
			}

			while (left <= right && arr[right] > pivot) {
				--right;
			}

			if (left < right) {
				swap(arr[left], arr[right]);
			}
		}

		swap(arr[first], arr[right]);
		return right;
	}
};

class MergeSort : public ISort {
public:
	virtual void Sort(int* arr, int len, int start = 0) override {
		if (len <= 1) return;

		int mid = len >> 1;
		int* leftArr = new int[mid];
		int* rightArr = new int[len - mid];

		memcpy(leftArr, arr, sizeof(int) * mid);
		memcpy(rightArr, arr + mid, sizeof(int) * (len - mid));
		Sort(leftArr, mid);
		Sort(rightArr, len - mid);

		Merge(arr, leftArr, mid, rightArr, len - mid);

		delete[] leftArr;
		delete[] rightArr;
	}

private:
	void Merge(int* arr, int* leftArr, int leftLen, int* rightArr, int rightLen) {
		int left = 0, right = 0, merge = 0;

		while (left < leftLen && right < rightLen) {
			if (leftArr[left] <= rightArr[right]) {
				arr[merge++] = leftArr[left++];
			}
			else {
				arr[merge++] = rightArr[right++];
			}
		}

		while (left < leftLen) {
			arr[merge++] = leftArr[left++];
		}

		while (right < rightLen) {
			arr[merge++] = rightArr[right++];
		}
	}

};

class HeapSort : public ISort {
	virtual void Sort(int* arr, int len, int start = 0) override {
		for (int i = (len >> 1) - 1; i >= 0; --i) {
			Heapify(arr, len, i);
		}

		cout << "힙 정렬 후: ";
		Print(arr, len);

		for (int i = len - 1; i >= 0; --i) {
			swap(arr[0], arr[i]);
			Heapify(arr, i, 0);
		}
	}

private:
	void Heapify(int* arr, int len, int index) {
		int largest, left, right;
		while (true) {
			largest = index;
			left = (index << 1) + 1;
			right = (index << 1) + 2;

			if (left < len && arr[left] > arr[largest]) {
				largest = left;
			}
			if (right < len && arr[right] > arr[largest]) {
				largest = right;
			}

			if (largest == index) break;
			swap(arr[index], arr[largest]);
			index = largest;
		}
	}
};