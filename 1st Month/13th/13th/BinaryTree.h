#pragma once
#include "Node.h"

using namespace std;

template<typename T>
class BinaryTree {
public:
	BinaryTree(const T& data) {
		root = new Node<T>(data);
	}

	~BinaryTree() {
		root->Destroy();
	}

	void AddLeftChild(const T& parentData, const T& childData) {
		Node<T>* outParent = nullptr;
		if (Find(parentData, &outParent)) {
			outParent->AddLeftChild(childData);
			return;
		}

		std::cout << "�θ� �˻� ���з� �߰� ����\n";
	}

	void AddRightChild(const T& parentData, const T& childData) {
		Node<T>* outParent = nullptr;
		if (Find(parentData, &outParent)) {
			outParent->AddRightChild(childData);
			return;
		}

		std::cout << "�θ� �˻� ���з� �߰� ����\n";
	}

	bool Find(const T& data, Node<T>** outNode) {
		return FindRecursive(data, root, outNode);
	}

	bool DeleteNode(const T& data) {
		Node<T>* outNode = nullptr;
		if (Find(data, &outNode)) {
			outNode->Destroy();
			return true;
		}
		cout << "������ ��� �˻� ����. ���� ����.\n";

		return false;
	}

	void PreOrderTraverse(int depth = 0) {
		cout << "���� ��ȸ ����-----------\n";
		PreOrderTraverseRecursive(root, depth);
		cout << "���� ��ȸ ��-----------\n";
	}

private:
	bool FindRecursive(const T& data, Node<T>* node, Node<T>** outNode) {
		if (!node)
		{
			*outNode = nullptr;
			return false;
		}

		if (node->data == data) {
			*outNode = node;
			return true;
		}

		if (FindRecursive(data, node->left, outNode)) {
			return true;
		}

		if (FindRecursive(data, node->right, outNode)) {
			return true;
		}

		*outNode = nullptr;
		return false;
	}

	void PreOrderTraverseRecursive(Node<T>* node, int depth) {
		if (!node) return;

		for (int i = 0; i < depth; ++i) {
			cout << " ";
		}

		cout << node->data << '\n';

		PreOrderTraverseRecursive(node->left, depth + 1);
		PreOrderTraverseRecursive(node->right, depth + 1);
	}

private:
	Node<T>* root = nullptr;
};