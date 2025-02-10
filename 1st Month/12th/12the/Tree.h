#pragma once
#include "Node.h"

using namespace std;

template<typename T>
class Tree {
	friend struct Node<T>;
public:
	Tree(const T& data) {
		root = new Node<T>(data);
	}

	~Tree() {
		DestroyRecursive(root);
	}

	void AddChild(const T& parentData, const T& childData) {
		Node<T>* parent = nullptr;
		if (FindNodeRecursive(parentData, root, &parent)) {
			parent->AddChild(childData);
			return;
		}
		
		cout << "부모 찾기 실패\n";
	}

	void AddChild(Node<T>* child, Node<T>* parent = nullptr) {
		child->parent = parent == nullptr ? root : parent;
		child->parent->AddChild(child);

	}

	void AddChild(const T& data, Node<T>* parent = nullptr) {
		AddChild(new Node<T>(data), parent);
	}

	bool Find(const T& data, Node<T>** outNode) {
		return FindNodeRecursive(data, root, outNode);
	}

	bool Remove(const T& data) {
		RemoveNodeRecursive(data, root);
	}

	void PreOrderTraverse(int depth = 0) {
		PreOrderTraverseRecursive(root, depth);
	}

private:

	void PreOrderTraverseRecursive(Node<T>* node, int depth = 0) {
		if (!node) return;
		for (int i = 0; i < depth; ++i) {
			std::cout << "  ";
		}

		std::cout << node->data << '\n';

		List<Node<T>*>* children = node->children;
		if (!children->Size()) return;

		for (int i = 0; i < children->Size(); ++i) {
			Node<T>* child = children->At(i);
			PreOrderTraverseRecursive(child, depth + 1);
		}
	}

	bool RemoveNodeRecursive(const T& data, Node<T>* node) {
		Node<T>* outNode = nullptr;
		if (FindNodeRecursive(data, node, outNode)) {
			Node<T>* parent = outNode->parent;
			if (parent) {
				parent->children->Remove(outNode);
			}

			List<Node<T>*>* children = outNode->children;
			while (children && children->Size()) {
				outNode->RemoveChild(children->At(0));
			}

			delete outNode;
			outNode = nullptr;

			return true;
		}

		return false;
	}

	void DestroyRecursive(Node<T>* node) {
		List<Node<T>*>* children = node->children;
		while (children && children->Size()) {
			Node<T>* child = children->At(0);
			DestroyRecursive(child);
		}

		Node<T>* parent = node->parent;
		if (parent) {
			parent->children->Remove(node);
		}

		delete node;
		node = nullptr;
	}

	bool FindNodeRecursive(const T& data, Node<T>* node, Node<T>** outNode) {
		if (!node) {
			*outNode = nullptr;
			return false;
		}

		if (node->data == data) {
			*outNode = node;
			return true;
		}

		List<Node<T>*>* children = node->children;
		int size = children->Size();
		for (int i = 0; i < size; ++i) {
			Node<T>* child = children->At(i);
			bool result = FindNodeRecursive(data, child, outNode);

			if (result) return true;
		}

		*outNode = nullptr;
		return false;
	}
private:
	Node<T>* root = nullptr;
};