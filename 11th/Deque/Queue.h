#pragma once
#include <iostream>

using namespace std;

template<typename T>
class Queue {
public:
	Queue()
		: capacity(4), front(0), rear(0)
	{
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	~Queue() {
		delete[] data;
		data = nullptr;
	}

	void Enqueue(const T& item) {
		if (rear == capacity) {
			if (front) {
				if (front == rear) front = rear = 0;
				else {
					rear -= front;
					memmove(data, data + front, sizeof(T) * rear);
					front = 0;
				}
			}

			else {
				capacity <<= 1;
				T* temp = new T[capacity];
				memcpy(temp, data, sizeof(T) * rear);
				delete[] data;
				data = temp;
			}
		}

		data[rear++] = item;
	}

	int Size() const {
		return front - rear;
	}

	bool Empty() const {
		return front == rear;
	}

	T Peek() {
		if (!Empty()) return data[front];

		cout << "Queue is Empty\n";
		return NULL;
	}

	bool TryDequeue(T& outValue) {
		outValue = Dequeue();
		return outValue != NULL;
	}

	T Dequeue() {
		if (!Empty()) return data[front++];

		cout << "Queue is Empty\n";
		return NULL;
	}

protected:
	T* data;
	int capacity;
	int front;
	int rear;
};