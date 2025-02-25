#pragma once
#include "Core.h"

template<typename T>
class PlacePool {
public:
	PlacePool(int size = 4)
		: count(0), capacity(size) {
        memoryPool = static_cast<T*>(malloc(sizeof(T) * size));
        if (!memoryPool) __debugbreak();
        memset(memoryPool, 0, sizeof(T) * size);
	}

	~PlacePool() {
		for (int i = 0; i < count; ++i) {
			memoryPool[i].~T();
		}
		delete[] memoryPool;
		memoryPool = nullptr;
	}

	template<typename... Args>
	T& MakeItem(Args&&... args) {
		if (count == capacity) {
			capacity <<= 1;
			T* temp = static_cast<T*>(malloc(sizeof(T) * capacity));
            if (!temp) __debugbreak();
			memset(temp, 0, sizeof(T) * capacity);
			memcpy(temp, memoryPool, capacity >> 1);
			delete[] memoryPool;
			memoryPool = temp;
		}

		new (&memoryPool[count++]) T(args ...);
        return memoryPool[count - 1];
	}

	int size() const {
		return this->count;
	}

	T* operator[](int index) {
		if (count <= index) __debugbreak();

		return &memoryPool[index];
	}

	void erase(int index) {
		if (count <= index) return;
		memoryPool[index].~T();
		if (index < --count)
			memoryPool[index] = std::move(memoryPool[count]);
		memset(memoryPool + sizeof(T) * (count + 1), 0, sizeof(T));
	}

	void Clear() {
		for (int i = 0; i < count; ++i) {
			memoryPool[i].~T();
		}
		memset(memoryPool, 0, count * sizeof(T));
		count = 0;
	}

private:
	T* memoryPool;
	int capacity;
	int count;
};