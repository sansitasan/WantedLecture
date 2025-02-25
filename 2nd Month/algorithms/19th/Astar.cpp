#include "Astar.h"
#include <iostream>

namespace San {
	AStar::AStar()
	{
	}

	AStar::~AStar()
	{
		for (Node* node : openSet) {
			--poses[node->position];
			SafeDelete(node);
		}
		openSet.clear();

		for (Node* node : closedSet) {
			--poses[node->position];
			SafeDelete(node);
		}
		closedSet.clear();
	}

	bool AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid, std::vector<Node*>* pathList)
	{
		this->startNode = startNode;
		this->goalNode = goalNode;
		openSet.emplace(startNode);
		++poses[startNode->position];

		if (!pathList) {
			pathList = new std::vector<Node*>();
		}

		std::vector<Dir> directions = {
			{ 0, 1, 1.f },
			{ 0, -1, 1.f },
			{ 1, 0, 1.f },
			{ -1, 0, 1.f },
			//대각선
			{ 1, 1, 1.41421356237f },
			{ 1, -1, 1.41421356237f },
			{ -1, 1, 1.41421356237f },
			{ -1, -1, 1.41421356237f },
		};

		while (!openSet.empty()) {
			//현재 리스트에서 비용(fCost)이 가장 낮은 노드 검색
			Node* currentNode = *(openSet.begin());

			if (IsDestination(currentNode)) {
				ConstructPath(currentNode, *pathList);
				return true;
			}

			openSet.erase(currentNode);

			if (closedSet.find(currentNode) != closedSet.end()) continue;
			closedSet.emplace(currentNode);

			for (const Dir& direction : directions) {
				//연산자 내가 만들기
				int newX = currentNode->position.x + direction.x;
				int newY = currentNode->position.y + direction.y;

				//범위 확인
				if (!IsInRange(newX, newY, grid)) continue;
				//벽 확인
				if (grid[newY][newX] == 1) continue;

				if (HasVisited(newX, newY, direction.cost + currentNode->gCost)) continue;

				Node* neighborNode = new Node(newX, newY, currentNode);
				neighborNode->gCost = direction.cost + currentNode->gCost;
				neighborNode->hCost = CalculteHeuristic(neighborNode, goalNode);
				neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

				if (*neighborNode == Node(13, 2)) {
					auto it = openSet.find(neighborNode);
					int x = 10;
				}

				//openList에서 찾고, 같은 위치가 있으면 비용 비교해서 업데이트 -> 이미 찾았음
				openSet.emplace(neighborNode);
				++poses[neighborNode->position];
			}
		}

		return false;
	}

	void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
	{
		for (const Node* node : path) {
			grid[node->position.y][node->position.x] = 2;
		}

		for (int y = 0; y < (int)grid.size(); ++y) {
			for (int x = 0; x < (int)grid[y].size(); ++x) {
				std::cout << (char)(grid[y][x] + 48);
			}
			std::cout << '\n';
		}

		for (const Node* node : path) {
			grid[node->position.y][node->position.x] = 0;
		}
	}

	inline void AStar::ConstructPath(Node* goalNode, std::vector<Node*>& pathList)
	{
		while (goalNode) {
			pathList.emplace_back(goalNode);
			goalNode = goalNode->parent;
		}

		std::reverse(pathList.begin(), pathList.end());
	}

	inline float AStar::CalculteHeuristic(Node* currentNode, Node* goalNode)
	{
		Position diff = *currentNode - *goalNode;
		return std::sqrt(diff.x * diff.x + diff.y * diff.y);
	}

	inline bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
	{
		return x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size();
	}

	inline bool AStar::HasVisited(int x, int y, float gCost)
	{
		Node n(x, y);
		for (auto it = openSet.begin(); it != openSet.end();) {
			Node* node = *it;
			if (*node != n) {
				++it;
				continue;
			}
			if (node->gCost <= gCost)
				return true;
			// 삭제 후 iterator를 갱신
			it = openSet.erase(it);
			--poses[node->position];
			SafeDelete(node);
		}

		for (auto it = closedSet.begin(); it != closedSet.end(); ) {
			Node* node = *it;
			if (*node != n) {
				++it;
				continue;
			}
			if (node->gCost <= gCost)
				return true;
			--poses[node->position];
			it = closedSet.erase(it);
			SafeDelete(node);
		}
		return false;
	}

	inline bool AStar::IsDestination(const Node* node)
	{
		return *node == *goalNode;
	}
}