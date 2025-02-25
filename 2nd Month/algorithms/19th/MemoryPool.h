#pragma once
#include <memory>

template<typename T>
class MemoryPool {
public:
	MemoryPool(int size = 4)
		: count(0), capacity(size) {
		memoryPool = static_cast<T*>(malloc(sizeof(T) * size));
		memset(memoryPool, 0, sizeof(T) * size);
	}

	~MemoryPool() {
		for (int i = 0; i < count; ++i) {
			memoryPool[i].~T();
		}
		delete[] memoryPool;
		memoryPool = nullptr;
	}

	template<typename... Args>
	void MakeItem(Args&&... args) {
		if (count == capacity) {
			capacity <<= 1;
			T* temp = static_cast<T*>(malloc(sizeof(T) * capacity));
			memset(temp, 0, sizeof(T) * capacity);
			memcpy(temp, memoryPool, capacity >> 1);
			delete[] memoryPool;
			memoryPool = temp;
		}

		new (&memoryPool[count++]) T(args ...);
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