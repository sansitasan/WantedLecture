#pragma once
#include <iostream>
#include <string>

template<typename T>
void SafeDelete(T*& t) {
	if (t) {
		delete t;
		t = nullptr;
	}
}

template<typename T>
struct Node {
	Node(const T& data, bool isBlack = false)
		: data(data), isBlack(isBlack) { }

	~Node() = default;

	const T Data() const { return data; }
	void SetData(const T& newData) { data = newData; }
	bool IsBlack() const { return isBlack; }
	void SetColor(bool isBlack) { this->isBlack = isBlack; }
	const char* ColorString() const {
		return isBlack ? "Black" : "Red";
	}

	Node<T>* Parent() const { return parent; }
	void SetParent(Node<T>* newParent) { parent = newParent; }

	Node<T>* Left() const { return leftChild; }
	void SetLeft(Node<T>* newLeft) { leftChild = newLeft; }

	Node<T>* Right() const { return rightChild; }
	void SetRight(Node<T>* newRight) { rightChild = newRight; }

private:
	T data;
	bool isBlack = false;

	Node<T>* parent = nullptr;
	Node<T>* leftChild = nullptr;
	Node<T>* rightChild = nullptr;
};