#pragma once
#include "List.h"

template<typename T>
struct Node {

	friend struct Node<T>;
	template<typename T>
	friend class Tree;

public:
	Node(const T& data = T()) 
		: data(data) 
	{
		children = new List<Node<T>*>();
	}

	Node(const Node& other) = delete;

	~Node() {
		parent = nullptr;
		delete children;
		children = nullptr;
	}

	void AddChild(const T& newData) {
		AddChild(new Node<T>(newData));
	}

	void AddChild(Node<T>* newChild) {
		newChild->parent = this;
		children->PushBack(newChild);
	}

	void RemoveChild(Node<T>& child) {
		RemoveChildRecursive(child);
	}

	int GetCount() {
		int count = 1;
		for (int i = 0; i < children->Size(); ++i) {
			count += children()->At(i)->GetCount();
		}

		return count;
	}

private:
	void RemoveChildRecursive(Node<T>* child) {
		if (!child) return;

		List<Node<T>*>* children = child->children;

		if (!children || !children->Size()) {

			child->parent->children->Remove(child);

			delete child;
			child = nullptr;

			return;
		}

		while (children && children->Size()) {
			RemoveChildRecursive(children->At(0));
		}

		child->parent->children->Remove(child);

		delete child;
		child = nullptr;
	}

private:
	T data;

	Node<T>* parent = nullptr;
	List<Node<T>*>* children = nullptr;
};