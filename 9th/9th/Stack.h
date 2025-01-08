#pragma once
#include <iostream>

template<typename T>
class Stack {
public:
	Stack() 
		:count(0), capacity(4)
	{
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	void Clear() {
		count = 0;
	}

	int Size() const {
		return count;
	}

	bool Empty() {
		return count == 0;
	}

	void Push(const T& item) {
		if (count == capacity) {
			capacity *= 1.5f;
			T* temp = new T[capacity];
			memmove(temp, data, sizeof(T) * count);
			delete[] data;
			data = temp;
		}
		data[count++] = item;
	}

	T Top() {
		if (Empty()) {
			std::cout << "stack is empty\n";
			return NULL;
		}

		return data[count];
	}

	T Pop() {
		if (Empty()) {
			std::cout << "stack is empty\n";
			return NULL;
		}

		return data[--count];
	}

	bool TryPop(T& outValue) {
		if (Empty()) {
			std::cout << "stack is empty\n";
			return false;
		}

		outValue = data[--count];
		return true;
	}

private:
	T* data;

	int count;
	int capacity;
};