#pragma once
#include <iostream>

// 이진 트리에 사용할 노드 클래스.
template<typename T>
class Node
{
    // 이진 탐색 트리를 프렌드로 선언.
    template<typename T>
    friend class BinarySearchTree;

public:
    Node(const T& data)
        : data(data), parent(nullptr), left(nullptr), right(nullptr)
    {
    }

    Node(const T& data, Node<T>* parent)
        : data(data), parent(parent), left(nullptr), right(nullptr)
    {
    }

    ~Node()
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

private:

    // 노드가 가지는 데이터.
    T data;

    // 부모 노드.
    Node<T>* parent;

    // 왼쪽 자손 노드.
    Node<T>* left;

    // 오른쪽 자손 노드.
    Node<T>* right;
};

template<typename T>
class BinarySearchTree
{
public:
	// 생성자.
	BinarySearchTree()
		: root(nullptr)
	{
	}

	// 소멸자.
	~BinarySearchTree()
	{
		Destroy();
	}

	// 삽입.
	// 규칙 ->
	// 0. 중복된 값은 허용하지 않는다.
	// 1. 시작 - 루트에서부터 비교 시작.
	// 1-1 루트가 null이면 새 노드를 루트로 지정한다.
	// 2. 새로 추가하는 값이 비교하는 노드보다 작으면 왼쪽 서브 트리로 비교를 이어간다.
	// 3. 새로 추가하는 값이 비교하는 노드보다 크면 오른쪽 서브 트리로 비교를 이어간다.
	bool InsertNode(const T& newData)
	{
		// 검색 (중복된 값이 있는지 확인) -> 허용 X.
		if (SearchNode(newData) == true)
		{
			std::cout << "Error: 이미 중복된 값이 있어 데이터를 추가하지 못했습니다.\n";
			return false;
		}

		// 루트가 nullptr이면 루트로 지정.
		if (root == nullptr)
		{
			root = new Node<T>(newData);
			return true;
		}

		// 2와 3의 경우를 위해 재귀 함수 작성 후 호출해야 함.
		root = InsertNodeRecursive(root, nullptr, newData);
		return true;
	}

	// 삭제.
	void DeleteNode(const T& deleteData)
	{
		// 재귀적으로 삭제하는 함수를 호출.
		// 삭제 연산의 시작은 Root 노드.
		// 예외 처리가 안된 코드.
		root = DeleteNodeRecursive(root, deleteData);
	}

	// 최소값 검색 함수.
	// node: 검색을 시작하는 노드.
	Node<T>* SearchMinValue(Node<T>* node)
	{
		// 검색 시작.
		// 왼쪽 서브 트리로 계속해서 이동하면서, 최소 값 검색.
		while (node->left != nullptr)
		{
			// 왼쪽 서브 노드로 이동.
			node = node->left;
		}

		// 최소 값을 가진 노드를 반환.
		return node;
	}

	// 검색.
	bool SearchNode(const T& data)
	{
		// 루트에서 시작해서 재귀적으로 검색을 진행.
		return SearchNodeRecursive(root, data);
	}

	bool SearchNodeRecursive(Node<T>* node, const T& data)
	{
		// 검색 실패.
		if (node == nullptr)
		{
			return false;
		}

		// 같으면 찾았다고 반환.
		if (node->data == data)
		{
			return true;
		}

		// 작은 경우 왼쪽으로.
		if (node->data > data)
		{
			return SearchNodeRecursive(node->left, data);
		}

		// 큰 경우 오른쪽으로.
		else
		{
			return SearchNodeRecursive(node->right, data);
		}
	}

	// 출력 (전위 순회).
	void PreorderTraverse(int depth = 0)
	{
		std::cout << "========== 전위 순회 시작 ==========\n";

		// 출력을 위해 전위 순회 방식으로 재귀 함수를 호출.
		// 탐색 시작은 루트 노트에서 부터.
		PreorderTraverseRecursive(root, depth);

		std::cout << "========== 전위 순회 종료 ==========\n";
	}

	// 출력 (중위 순회).
	void InorderTraverse(int depth = 0)
	{
		std::cout << "========== 중위 순회 시작 ==========\n";

		// 출력을 위해 중위 순회 방식으로 재귀 함수를 호출.
		// 탐색 시작은 루트 노트에서 부터.
		InorderTraverseRecursive(root, depth);

		std::cout << "========== 중위 순회 종료 ==========\n";
	}

	// 출력 (후위 순회).
	void PostorderTraverse(int depth = 0)
	{
		std::cout << "========== 후위 순회 시작 ==========\n";

		// 출력을 위해 후위 순회 방식으로 재귀 함수를 호출.
		// 탐색 시작은 루트 노트에서 부터.
		PostorderTraverseRecursive(root, depth);

		std::cout << "========== 후위 순회 종료 ==========\n";
	}

private:
	// 재귀적으로 삽입을 처리하는 함수.
	// node: 현재 비교하는 노드.
	// parent: node의 부모 노드.
	// newData: 삽입하려는 새 데이터.
	Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& newData)
	{
		// node가 nullptr이면 새로 생성 후 생성한 노드를 반환.
		if (node == nullptr)
		{
			// 새 노드 생성 후 반환.
			return new Node<T>(newData, parent);
		}

		// 추가하려는 값이 비교 노드보다 작으면, 왼쪽 서브 트리로 탐색.
		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(node->left, node, newData);
		}

		// 추가하려는 값이 비교 노드보다 크면, 오른쪽 서브 트리로 탐색.
		else
		{
			node->right = InsertNodeRecursive(node->right, node, newData);
		}

		return node;
	}

	// 삭제 재귀 함수.
	Node<T>* DeleteNodeRecursive(Node<T>* node, const T& deleteData)
	{
		// 종료 조건.
		// 노드가 null이면 삭제할 노드를 찾지 못한 것이기 때문에 null을 반환하고 종료.
		if (node == nullptr)
		{
			return nullptr;
		}

		// 삭제하려는 데이터가 비교 데이터보다 작으면 왼쪽 서브 트리로 이동.
		if (node->data > deleteData)
		{
			node->left = DeleteNodeRecursive(node->left, deleteData);
		}

		// 삭제하려는 데이터가 비교 데이터보다 크면 오른쪽 서브 트리로 이동.
		else if (node->data < deleteData)
		{
			node->right = DeleteNodeRecursive(node->right, deleteData);
		}

		// 찾으면, 삭제 처리.
		else
		{
			// 경우1 - 자식이 없는 경우. (둘 모두 null인 경우)
			if (node->left == nullptr && node->right == nullptr)
			{
				// 노드 삭제 후 함수 종료.
				delete node;
				return nullptr;
			}

			// 경우3 - 자식이 둘 다 있는 경우. (둘 모두 null이 아닌 경우).
			if (node->left != nullptr && node->right != nullptr)
			{
				// 삭제되는 노드의 오른쪽 서브 트리에서 가장 작은 값을 검색해서 삭제하는 노드의 값을 업데이트.
				node->data = SearchMinValue(node->right)->data;

				// 위에서 구한 오른쪽 서브 트리에서 가장 작은 값을 가진 노드를 삭제.
				node->right = DeleteNodeRecursive(node->right, node->data);
			}
			else
			{
				// 경우2 - 자식이 하나만 있는 경우 (둘 중 하나만 null인 경우).
				if (node->left == nullptr)
				{
					// 오른쪽 자손을 반환하기 위해 임시로 포인터 저장.
					Node<T>* right = node->right;

					// 노드 제거.
					delete node;

					// 오른쪽 자손 반환.
					return right;
				}

				else if (node->right == nullptr)
				{
					// 왼쪽 자손을 반환하기 위해 임시로 포인터 저장.
					Node<T>* left = node->left;

					// 노드 제거.
					delete node;

					// 왼쪽 자손 반환.
					return left;
				}
			}
		}

		return node;
	}

	// 전위 순회 재귀 함수.
	void PreorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (node == nullptr)
		{
			// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리.
		std::cout << node->data << "\n";

		// 왼쪽 서브 트리를 전위 순회.
		PreorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 서브 트리를 전위 순회.
		PreorderTraverseRecursive(node->right, depth + 1);
	}

	// 중위 순회 재귀 함수.
	void InorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (node == nullptr)
		{
			// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// 왼쪽 서브 트리를 중위 순회.
		InorderTraverseRecursive(node->left, depth + 1);

		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리.
		std::cout << node->data << "\n";

		// 오른쪽 서브 트리를 중위 순회.
		InorderTraverseRecursive(node->right, depth + 1);
	}

	// 후위 순회 재귀 함수.
	void PostorderTraverseRecursive(Node<T>* node, int depth = 0)
	{
		// 종료 조건.
		if (node == nullptr)
		{
			// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
			for (int ix = 0; ix < depth; ++ix)
			{
				std::cout << "  ";
			}

			std::cout << "null\n";
			return;
		}

		// 왼쪽 서브 트리를 후위 순회.
		PostorderTraverseRecursive(node->left, depth + 1);

		// 오른쪽 서브 트리를 후위 순회.
		PostorderTraverseRecursive(node->right, depth + 1);

		// 트리 노드를 출력할 때 계층을 보여주기 위해 빈 공간 출력.
		for (int ix = 0; ix < depth; ++ix)
		{
			std::cout << "  ";
		}

		// 부모 노드 처리.
		std::cout << node->data << "\n";
	}

private:
	// 모든 노드를 제거할 때 사용하는 함수.
	void Destroy()
	{
		// 루트 노드가 null이면 종료.
		if (root == nullptr)
		{
			return;
		}

		// 왼쪽 자손 > 오른쪽 자손 > 루트 순으로 제거.
		DestroyRecursive(root);
	}

	void DestroyRecursive(Node<T>* node)
	{
		// 재귀함수 종료 조건.
		if (node == nullptr)
		{
			return;
		}

		// 왼쪽 자손 / 오른쪽 자손 확인.
		Node<T>* left = node->left;
		Node<T>* right = node->right;

		// 자손이 없는 경우.
		if (left == nullptr && right == nullptr)
		{
			// 노드 삭제 후 함수 종료.
			delete node;
			return;
		}

		DestroyRecursive(left);
		DestroyRecursive(right);

		delete node;
	}

private:

	// 루트 노드.
	Node<T>* root;
};