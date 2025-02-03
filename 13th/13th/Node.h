#pragma once
#include "List.h"

#include <iostream>

template<typename T>
struct Node {
	template<typename T>
	friend class BinaryTree;

public:
	Node(const T& data = T())
		: data(data)
	{
	}

	Node(const Node& other) = delete;

	~Node() {
		parent = nullptr;
	}

	void AddLeftChild(Node<T>* child) {
		child->parent = this;

		left = child;
	}

	void AddLeftChild(const T& data) {
		AddLeftChild(new Node<T>(data));
	}

	void AddRightChild(Node<T>* child) {
		child->parent = this;

		right = child;
	}

	void AddRightChild(const T& data) {
		AddRightChild(new Node<T>(data));
	}

	void Destroy() {
		if (parent) {
			if (parent->left == this) {
				parent->left = nullptr;
			}

			else if (parent->right == this) {
				parent->right = nullptr;
			}
		}

		Node<T>* self = this;
		DestroyRecursive(&self);
	}

private:
	void DestroyRecursive(Node<T>** node) {
		if (!(*node)) return;

		Node<T>** leftChild = &((*node)->left);
		Node<T>** rightChild = &((*node)->right);

		DestroyRecursive(leftChild);
		DestroyRecursive(rightChild);

		delete *node;
		*node = nullptr;
	}

private:
	T data;

	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};