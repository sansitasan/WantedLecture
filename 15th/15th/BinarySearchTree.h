#pragma once
#include <iostream>

//<>는 프로젝트가 아는 경로만
//외부, 표준 라이브러리는 보통 <>을 관성적으로 사용
//#include

//오브젝트 - 객체지향 설계 방법 책
//객체 지향의 사실과 오해 - 왜 SOLID가 나왔는가
template<typename T>
class Node {
	template<typename T>
	friend class BST;

public:
	Node() {

	}

	Node(const T& data) 
		: data(data) {
	}

	Node(const T& data, Node<T>* parent) 
		: data(data), parent(parent) {

	}

	~Node() {
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

private:
	T data;

	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};

template<typename T>
class BST {
public:
	BST() = default;

	~BST() {
		//TODO: 재귀 삭제
	}

	bool SearchNode(const T& data) {
		return SearchNodeRecursive(root, data);
	}

	bool AddNode(const T& data) {
		Node<T>* newNode = root;
		bool ret = SearchNodeRecursive(newNode, data);

		if (ret) {
			std::cout << "Error: 중복된 값이 있습니다!\n";
			return false;
		}

		if (!root) {
			root = new Node<T>(data);
			return true;
		}

		InsertNodeRecursive(root, nullptr, data);

		return true;
	}

	void DeleteNode(const T& deleteData) {
		root = DeleteNodeRecursive(root, deleteData);
	}

	void Clear() {
		if (!root) return;
		ClearRecursive(root);
	}

private:
	bool SearchNodeRecursive(Node<T>* node, const T& data) {
		if (!node) return false;
		if (node->data == data) return true;

		Node<T>* child = node->data > data ? node->left : node->right;
		return SearchNodeRecursive(child, data);
	}

	Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& data) {
		if (!node) return new Node<T>(data, parent);

		Node<T>** child = node->data > data ? &node->left : &node->right;
		*child = InsertNodeRecursive(*child, node, data);

		return node;
	}

	Node<T>* DeleteNodeRecursive(Node<T>* node, const T& deleteData) {
		if (!node) return nullptr;
		if (node->data != deleteData) {
			Node<T>** child = node->data > deleteData ? &node->left : &node->right;

			*child = DeleteNodeRecursive(*child, deleteData);
			return node;
		}

		if (node->left == nullptr && node->right == nullptr)
		{
			delete node;
			return nullptr;
		}

		if (node->left && node->right) {
			Node<T>** t = SearchMinValue(node->right);
			node->data = (*t)->data;
			node->right = DeleteNodeRecursive(node->right, node->data);
			return node;
		}

		Node<T>* temp = nullptr;

		if (node->left) {
			temp = node->left;
		}

		else {
			temp = node->right;
		}
		delete node;
		return temp;
	}

	Node<T>** SearchMinValue(Node<T>* node) {
		if (!node) return nullptr;

		while (node->left) {
			node = node->left;
		}

		return &node;
	}

	void ClearRecursive(Node<T>* node) {
		if (!node) return;

		ClearRecursive(node->left);
		ClearRecursive(node->right);
		delete node;
	}

private:
	Node<T>* root = nullptr;
};