#pragma once
#include <iostream>

template<typename T>
class Deque {
public:
	Deque() : capacity(8), front(4), rear(4) {
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	~Deque() {
		delete[] data;
	}

	bool Empty() {
		return front == rear;
	}

	void PushFront(const T& item) {
		if (front == -1) {
			front = capacity;
			rear += front;
			capacity <<= 1;
			T* temp = new T[capacity];
			memcpy(temp + front, data, sizeof(T) * front);
			delete[] data;
			data = temp;
		}

		data[front--] = item;
	}

	void PushFront(const T& item) {
		if (rear == capacity) {
			front = capacity;
			rear += front;
			capacity <<= 1;
			T* temp = new T[capacity];
			memcpy(temp + front, data, sizeof(T) * front);
			delete[] data;
			data = temp;
		}

		data[front--] = item;
	}

private:
	T* data;
	int capacity;
	int front;
	int rear;
};