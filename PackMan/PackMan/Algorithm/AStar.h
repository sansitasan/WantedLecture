#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

struct Node {
    int x, y;
    double gCost, hCost, fCost;
    Node* parent;

    Node(int x, int y) : x(x), y(y), gCost(0), hCost(0), fCost(0), parent(nullptr) {}

    // Define comparison operator for priority queue
    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

using Grid = std::vector<std::vector<int>>; // 0 = walkable, 1 = obstacle

// Manhattan distance as the heuristic
double Heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

std::vector<Node*> GetNeighbors(Node* current, const Grid& grid) {
    std::vector<Node*> neighbors;
    int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    for (auto& dir : directions) {
        int nx = current->x + dir[0];
        int ny = current->y + dir[1];

        if (nx >= 0 && ny >= 0 && nx < grid[0].size() && ny < grid.size() && grid[ny][nx] == 0) {
            neighbors.push_back(new Node(nx, ny));
        }
    }
    return neighbors;
}

std::vector<Node*> AStar(Grid& grid, int startX, int startY, int targetX, int targetY, int width, int height) {
    auto compare = [](Node* a, Node* b) { return *a > *b; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openList(compare);
    std::unordered_map<int, Node*> closedList;

    Node* startNode = new Node(startX, startY);
    startNode->hCost = Heuristic(startX, startY, targetX, targetY);
    startNode->fCost = startNode->gCost + startNode->hCost;

    openList.push(startNode);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == targetX && current->y == targetY) {
            std::vector<Node*> path;
            while (current) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        int key = current->y * width + current->x;
        closedList[key] = current;

        for (auto& neighbor : GetNeighbors(current, grid)) {
            int neighborKey = neighbor->y * width + neighbor->x;

            if (closedList.find(neighborKey) != closedList.end()) {
                delete neighbor;
                continue;
            }

            double tentativeGCost = current->gCost + 1;

            if (tentativeGCost < neighbor->gCost || neighbor->gCost == 0) {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = Heuristic(neighbor->x, neighbor->y, targetX, targetY);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;

                openList.push(neighbor);
            }
        }
    }

    return {}; // No path found
}