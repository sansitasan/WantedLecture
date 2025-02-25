#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>

#ifdef _DEBUG
#define New new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

//������ ���
//Set�� Compare���� ���ٰ� ������ ���Ҵ� �߰����� �ʴ´�.
//�Ҽ���� �ص� ���ٰ� �����Ǵ� ���Ҵ� ������ �� �ִ�.
//���� ������ �߰��ؾ� �Ѵ�.
namespace San {
	template<typename T>
	void SafeDelete(T*& t) {
		if (t) {
			delete t;
			t = nullptr;
		}
	}

	struct Position {
		Position(int x = 0, int y = 0)
			: x(x), y(y) {
		}

		int x;
		int y;

		inline bool operator==(const Position& other) const {
			return x == other.x && y == other.y;
		}

		inline bool operator!=(const Position& other) const {
			return x != other.x || y != other.y;
		}
	};

	class Node {
	public:
		inline Node(int x, int y, Node* parent = nullptr)
			: position(x, y), parent(parent) {
		}

		inline ~Node() = default;

		inline Position operator-(const Node& other) {
			return Position(position.x - other.position.x, position.y - other.position.y);
		}

		inline Position operator+(const Node& other) {
			return Position(position.x + other.position.x, position.y + other.position.y);
		}

		inline bool operator==(const Node& other) const {
			return position.x == other.position.x && position.y == other.position.y;
		}

		//TODO: Fuck
		inline bool operator<(const Node& other) const {
			return position.x < other.position.x && position.y < other.position.y;
		}

		inline bool operator!=(const Node& other) const {
			return position.x != other.position.x || position.y != other.position.y;
		}

	public:
		Position position;

		//���� ��忡�� �̵� ������ ���
		float gCost = 0;
		//�޸���ƽ
		float hCost = 0;
		//f = g + h ���� ���
		float fCost = 0;

		//�θ� ����� ��ġ �ʿ�
		Node* parent = nullptr;
	};

	class AStar {
	private:
		struct Dir {
			int x = 0;
			int y = 0;

			float cost = 0;
		};
	public:
		AStar();
		~AStar();

		//��� �˻� �Լ�
		bool FindPath(
			Node* startNode,
			Node* goalNode,
			const std::vector<std::vector<int>>& grid,
			std::vector<Node*>* pathList);

		//�׸��� ��� �Լ�
		void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

	private:
		//���� ��� ��ȯ �Լ�
		//��ǥ��忡�� �θ� ��� ������
		inline void ConstructPath(Node* goalNode, std::vector<Node*>& pathList);

		//hCost ��� �Լ�
		inline float CalculteHeuristic(Node* currentNode, Node* goalNode);

		//Ž�� ��ġ�� ���� ���� �ִ���
		inline bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

		//�湮 ����
		//����� �θ� ��� �� ������Ʈ�� ���� �Ѱ��ش�
		inline bool HasVisited(int x, int y, float gCost);

		//Ž�� ��ġ�� ��ǥ ��ġ���� Ȯ��
		inline bool IsDestination(const Node* node);
	private:
		struct Compare {
			bool operator()(const Node* a, const Node* b) const {
				return a->fCost < b->fCost;
			}
		};

		struct NodeEqual {
			bool operator()(const Node* a, const Node* b) const {
				return *a == *b;
			}
		};

		struct NodeHash {
			size_t operator()(const Node* node) const {
				return std::hash<int>()(node->position.x) ^ std::hash<int>()(node->position.y);
			}
		};

		struct PosEqual {
			bool operator()(const Position& a, const Position& b) const {
				return a == b;
			}
		};

		struct PosHash {
			size_t operator()(const Position& position) const {
				return std::hash<int>()(position.x) ^ std::hash<int>()(position.y);
			}
		};

		std::multiset<Node*, Compare> openMulSet;
		std::set<Node*, Compare> openSet;
		std::unordered_set<Node*, NodeHash, NodeEqual> closedSet;
		std::unordered_map<Position, int, PosHash, PosEqual> poses;
		Node* startNode = nullptr;
		Node* goalNode = nullptr;
	};
}