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

//오늘의 찐빠
//Set의 Compare에서 같다고 판정된 원소는 추가되지 않는다.
//소수라고 해도 같다고 판정되는 원소는 존재할 수 있다.
//따라서 조건을 추가해야 한다.
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

		//현재 노드에서 이동 노드까지 비용
		float gCost = 0;
		//휴리스틱
		float hCost = 0;
		//f = g + h 최종 비용
		float fCost = 0;

		//부모 노드의 위치 필요
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

		//경로 검색 함수
		bool FindPath(
			Node* startNode,
			Node* goalNode,
			const std::vector<std::vector<int>>& grid,
			std::vector<Node*>* pathList);

		//그리드 출력 함수
		void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

	private:
		//최적 경로 반환 함수
		//목표노드에서 부모 노드 역추적
		inline void ConstructPath(Node* goalNode, std::vector<Node*>& pathList);

		//hCost 계산 함수
		inline float CalculteHeuristic(Node* currentNode, Node* goalNode);

		//탐색 위치가 범위 내에 있는지
		inline bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

		//방문 여부
		//비용이 싸면 비용 값 업데이트를 위해 넘겨준다
		inline bool HasVisited(int x, int y, float gCost);

		//탐색 위치가 목표 위치인지 확인
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