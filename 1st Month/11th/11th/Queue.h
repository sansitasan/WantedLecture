#pragma once

#include <iostream>

template<typename T, int size = 10>
class Queue
{
public:
	Queue()
		: front(0), rear(0)
	{
		memset(data, 0, sizeof(T) * size);
	}

	bool IsEmpty()
	{
		return front == rear;
	}

	bool IsFull()
	{
		return (rear + 1) % size == front;
	}

	bool Enqueue(const T& value)
	{
		if (IsFull() == true)
		{
			std::cout << "Error: 큐가 가득 차 있습니다." << std::endl;
			return false;
		}

		rear = (rear + 1) % size;
		data[rear] = value;
		return true;
	}

	bool Dequeue(T& outValue)
	{
		if (IsEmpty() == true)
		{
			std::cout << "Error: 큐가 비어 있습니다." << std::endl;
			return false;
		}

		front = (front + 1) % size;
		outValue =  data[front];
		return true;
	}

	T Peek()
	{
		if (IsEmpty() == true)
		{
			std::cout << "Error: 큐가 비어 있습니다." << std::endl;
		}
		else
		{
			return data[(front + 1) % size];
		}
	}

	void Display()
	{
		std::cout << "큐 내용: ";

		int max = (front < rear) ? rear : rear + size;
		for (int ix = front + 1; ix <= max; ++ix)
		{
			std::cout << " " << data[ix % size];
		}

		std::cout << std::endl;
	}

private:
	int front;
	int rear;
	T data[size];
};