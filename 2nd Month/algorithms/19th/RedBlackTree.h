#pragma once
//null이 아닌 nil인 이유
//색을 구분하기 위해
#include "Node.h"
#include <Windows.h>

enum ETextColor {
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
	BrightWhite = FOREGROUND_INTENSITY | White
};

void SetTextColor(ETextColor color) {
	static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, color);
}

template<typename T>
class RedBlackTree {
public:
	RedBlackTree() {
		root = GetNilNode();
	}

	~RedBlackTree() {
		DestroyRecursive(root);
		Node<T>* nil = GetNilNode();
		SafeDelete(nil);
	}

	bool Find(const T& data, Node<T>** outNode) {
		if (root == GetNilNode()) return false;

		return FindRecursive(root, outNode, data);
	}

	void Insert(const T& data) {
		Node<T>* newNode = nullptr;
		if (Find(data, &newNode)) {
			std::cout << "오류 - 노드 추가 실패: 중복 값 존재. 입력 값: " << data << '\n';
			return;
		}

		newNode = CreateNode(data, false);
		Insert(newNode);
	}

	void Print(int depth = 0, int blackCount = 0) {
		PrintRecursive(root, depth, blackCount);
	}

	void Remove(const T& data) {
		Node<T>* node = nullptr;
		if (!Find(data, &node)) {
			std::cout << "오류: 해당 값을 가진 노드가 존재하지 않음. (검색 값: " << data << ")\n";
			return;
		}

		RemoveImpl(node);

	}

private:
	Node<T>* GetNilNode() {
		static Node<T>* nil = new Node<T>(0, true);
		return nil;
	}

	Node<T>* CreateNode(const T& data, bool isBlack) {
		Node<T>* newNode = new Node<T>(data, isBlack);
		newNode->SetLeft(GetNilNode());
		newNode->SetRight(GetNilNode());

		return newNode;
	}

	bool FindRecursive(Node<T>* node, Node<T>** outNode, const T& data) {
		if (node == GetNilNode()) return false;
		if (node->Data() == data) {
			*outNode = node;
			return true;
		}

		return node->Data() > data ? 
			FindRecursive(node->Left(), outNode, data) : 
			FindRecursive(node->Right(), outNode, data);
	}

	void Insert(Node<T>* newNode) {
		Node<T>* nil = GetNilNode();
		if (root == nil) {
			root = newNode;
			root->SetColor(true);
			return;
		}

		InsertRecursive(root, newNode);

		ReStructureAfterInsert(newNode);
	}

	void InsertRecursive(Node<T>* node, Node<T>* newNode) {

		bool isSmall = node->Data() > newNode->Data() ? true : false;
		Node<T>* child = isSmall ? node->Left() : node->Right();
		if (child == GetNilNode()) {
			newNode->SetParent(node);
			isSmall ? node->SetLeft(newNode) : node->SetRight(newNode);
			return;
		}

		InsertRecursive(child, newNode);

		ReStructureAfterInsert(newNode);
	}

	void ReStructureAfterInsert(Node<T>* newNode) {
		//부모 노드가 빨간색이면 연속 빨간색이 된다 조심(Red-Red Conflict)
		while (newNode != root && !newNode->Parent()->IsBlack()) {
			Node<T>* uncle = nullptr;
			if (newNode->Parent() == newNode->Parent()->Parent()->Left()) {
				uncle = newNode->Parent()->Parent()->Right();

				//Case1
				if (!uncle->IsBlack()) {
					newNode->Parent()->SetColor(true);
					newNode->Parent()->Parent()->SetColor(false);
					uncle->SetColor(true);
					newNode = newNode->Parent()->Parent();
					continue;
				}

				//Case2
				if (newNode == newNode->Parent()->Right()) {
					newNode = newNode->Parent();
					RotateToLeft(newNode);
				}
				
				//Case3
				newNode->Parent()->SetColor(true);
				newNode->Parent()->Parent()->SetColor(false);
				RotateToRight(newNode->Parent()->Parent());
			}

			else {
				uncle = newNode->Parent()->Parent()->Left();

				if (!uncle->IsBlack()) {
					newNode->Parent()->SetColor(true);
					newNode->Parent()->Parent()->SetColor(false);
					uncle->SetColor(true);
					newNode = newNode->Parent()->Parent();
					continue;
				}

				if (newNode == newNode->Parent()->Left()) {
					newNode = newNode->Parent();
					RotateToRight(newNode);
				}

				//Case3
				newNode->Parent()->SetColor(true);
				newNode->Parent()->Parent()->SetColor(false);
				RotateToLeft(newNode->Parent()->Parent());
			}
		}

		root->SetColor(true);
	}

	//피벗을 받는다
	void RotateToLeft(Node<T>* node) {
		Node<T>* right = node->Right();

		node->SetRight(right->Left());
		if (right->Left() != GetNilNode()) {
			right->Left()->SetParent(node);
		}

		right->SetParent(node->Parent());

		if (right->Parent() == nullptr) {
			root = right;
		}

		else {
			if (node == node->Parent()->Left()) {
				node->Parent()->SetLeft(right);
			}
			else {
				node->Parent()->SetRight(right);
			}
		}

		right->SetLeft(node);
		node->SetParent(right);
	}

	void RotateToRight(Node<T>* node) {
		Node<T>* left = node->Left();

		node->SetLeft(left->Right());
		if (left->Right() != GetNilNode()) {
			left->Right()->SetParent(node);
		}

		left->SetParent(node->Parent());

		if (left->Parent() == nullptr) {
			root = left;
		}

		else {
			if (node == node->Parent()->Left()) {
				node->Parent()->SetLeft(left);
			}
			else {
				node->Parent()->SetRight(left);
			}
		}

		left->SetRight(node);
		node->SetParent(left);
	}

	void DestroyRecursive(Node<T>* node) {
		if (node == GetNilNode()) return;
		DestroyRecursive(node->Left());
		DestroyRecursive(node->Right());
		SafeDelete(node);
	}

	void PrintRecursive(Node<T>* node, int depth, int blackCount) {
		if (node == GetNilNode()) return;

		if (node->IsBlack()) ++blackCount;

		T parentData = NULL;
		const char* position = "Root";

		if (node->Parent()) {
			parentData = node->Parent()->Data();

			node == node->Parent()->Left() ? position = "Left" : position = "Right";
		}

		char blackCountString[50] = {};
		if (node->Left() == GetNilNode() && node->Right() == GetNilNode()) {
			sprintf_s(blackCountString, "------ %d", blackCount);
		}

		for (int i = 0; i < depth; ++i) {
			std::cout << "  ";
		}

		node->IsBlack() ? SetTextColor(ETextColor::BrightWhite) : SetTextColor(ETextColor::Red);
		std::cout << node->Data() << " " << node->ColorString() << " [" << position << ", " << parentData << "] " << blackCountString << '\n';
		SetTextColor(ETextColor::White);
 
		PrintRecursive(node->Left(), depth + 1, blackCount);
		PrintRecursive(node->Right(), depth + 1, blackCount);
	}

	Node<T>* FindMinRecursive(Node<T>* node) {
		if (node == GetNilNode()) return nullptr;

		if (node->Left() == GetNilNode()) return node;
		return FindMinRecursive(node->Left());
	}

	Node<T>* FindMaxRecursive(Node<T>* node) {
		if (node == GetNilNode()) return nullptr;

		if (node->Right() == GetNilNode()) return node;
		return FindMaxRecursive(node->Right());
	}

	void RemoveImpl(Node<T>* node) {
		Node<T>* removed = node;
		Node<T>* trail = nullptr;
		Node<T>* nil = GetNilNode();

		if (node->Left() == nil && node->Right() == nil) {

		}

		else if (node->Left() != nil && node->Right() != nil) {
			removed = FindMaxRecursive(node->Left());
			node->SetData(removed->Data());
			removed == removed->Parent()->Left() ? removed->Parent()->SetLeft(nil) : removed->Parent()->SetRight(nil);
		}

		else {
			trail = node->Left() == nil ? node->Right() : node->Left();
			trail->SetParent(removed->Parent());
			if (!removed->Parent()) root = trail;
			else {
				removed == removed->Parent()->Left() ? 
					removed->Parent()->SetLeft(trail) : 
					removed->Parent()->SetRight(trail);
			}
		}

		if (removed->IsBlack() && trail) {
			ReStructureAfterInsert(removed);
		}

		SafeDelete(removed);
	}

private:
	Node<T>* root = nullptr;
};