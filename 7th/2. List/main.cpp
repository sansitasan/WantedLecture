#include <iostream>

using namespace std;

template<typename List>
class ListIterator {
public:
	using ValueType = typename List::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ListIterator(PointerType pointer)
		: pointer(pointer)
	{

	}

	//포인터 전위 증가 연산자 오버로딩
	ListIterator& operator++() {
		++pointer;
		return *this;
	}

	//후위 증가 연산자
	ListIterator& operator++(int) {
		ListIterator iterator = *this;
		++(*this);
		return iterator;
	}

	ListIterator& operator--() {
		--pointer;
		return *this;
	}

	ListIterator& operator--(int) {
		ListIterator iterator = *this;
		--(*this);
		return *this;
	}

	ReferenceType operator[](int idx) {
		return *(pointer + idx);
	}

	PointerType operator->() {
		return pointer;
	}

	ReferenceType operator*()
	{
		return *pointer;
	}

	bool operator==(const ListIterator& other) const
	{
		return pointer == other.pointer;
	}

	bool operator!=(const ListIterator& other) const
	{
		return !(*this == other);
	}

private:
	PointerType pointer;
};

//typename = class
//예전 문법으로는 class를 더 썼다
template<typename T>
class List {
public:
	using ValueType = T;
	using Iterator = ListIterator<List<T>>;

public:
	List() {
		data = new T[capacity];
	}

	List(int size) : count(size) {
		while (size >= capacity) {
			capacity <<= 1;
		}
		data = new T[capacity];
		memset(data, 0, sizeof(T) * count);
	}

	~List() {
		if (data != nullptr) {
			delete[] data;
		}
	}

	T& operator[](int index) {
		if (index > -1 && index < count) {
			return data[index];
		}
		else if (index == -1) {
			return data[size - 1];
		}

		//잘못된 접근
		__debugbreak();
	}

	const T& operator[](int index) const {
		if (index > -1 && index < count) {
			return data[index];
		}
		else if (index == -1) {
			return data[size - 1];
		}

		//잘못된 접근
		__debugbreak();
	}


	int Capacity() const { return capacity; }
	int Size() const { return count; }

	void PushBack(const T& value) {
		if (count == capacity) {
			ReAllocate();
		}
		data[count++] = value;
	}

	void EmplaceBack(T&& value) {
		if (count == capacity) {
			ReAllocate();
		}
		data[count++] = std::move(value);
	}

	T* Data() const { return data; }

	T& At(int index) {
		if (index >= count) {
			__debugbreak();
		}

		return data[index];
	}

	const T& At(int index) const {
		if (index >= count) {
			__debugbreak();
		}

		return data[index];
	}

	Iterator begin()
	{
		return Iterator(data);
	}

	Iterator end()
	{
		return Iterator(data + count);
	}

private:
	void ReAllocate() {
		capacity <<= 1;
		T* temp = new T[capacity];
		memset(temp, 0, sizeof(T) * capacity);
		memmove(temp, data, sizeof(T) * count);
		delete[] data;
		data = temp;
	}

private:
	int capacity = 2;
	int count = 0;
	T* data = nullptr;
};

int main() {
	List<int> list;
	for (int i = 0; i < 100; ++i) {
		list.PushBack(i);
	}

	//Range-Based Loop, Ranged Loop
	//열거형, 반복자, iterator
	for (const auto& item : list) {
		cout << item << " ";
	}

	char buffer[256];
	snprintf(buffer, 256, "%d, %d\n", list.Size(), list.Capacity());

	cout << buffer;
	return 0;
}