#include "Astar.h"
#include "Core.h"
#include <Engine/Engine.h>

AStar::~AStar()
{
    Clear();
}

bool AStar::FindPath(Node* startNode, Node* goalNode, std::vector<Vector2>& pathList)
{
    this->startNode = startNode;
    startNode->hCost = CalculteHeuristic(startNode, goalNode);
    this->goalNode = goalNode;
    openQ.emplace(startNode);

    std::vector<Dir> directions = {
        { 0, 1, 1.f },
        { 0, -1, 1.f },
        { 1, 0, 1.f },
        { -1, 0, 1.f },
        { 1, 1, 1.414214f },
        { 1, -1, 1.414214f },
        { -1, 1, 1.414214f },
        { -1, -1, 1.414214f },
    };

    while (!openQ.empty()) {
        //현재 리스트에서 비용(fCost)이 가장 낮은 노드 검색
        Node* currentNode = openQ.top();

        if (IsDestination(currentNode)) {
            ConstructPath(currentNode, pathList);
            Clear();
            return true;
        }

        openQ.pop();

        if (closedSet.find(currentNode) != closedSet.end()) continue;
        closedSet.emplace(currentNode);

        for (const Dir& direction : directions) {
            int newX = (int)currentNode->position.GetX() + direction.x;
            int newY = (int)currentNode->position.GetY() + direction.y;

            if (!IsInRange(newX, newY)) continue;

            Node x = Node(newX, newY);
            if (closedSet.find(&x) != closedSet.end()) continue;
            float hCost = CalculteHeuristic(&x, goalNode);
            if (hCost > currentNode->hCost) continue;

            Node* neighborNode = new Node(newX, newY, currentNode);
            neighborNode->gCost = direction.cost + currentNode->gCost;
            neighborNode->hCost = hCost;
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
            openQ.emplace(neighborNode);
        }
    }

    return false;
}

void AStar::Clear()
{
    while (!openQ.empty()) {
        Node* node = openQ.top();
        openQ.pop();
        SafeDelete(&node);
    }

    for (Node* node : closedSet) {
        SafeDelete(&node);
    }
    closedSet.clear();

    SafeDelete(&goalNode);
}

inline void AStar::ConstructPath(Node* goalNode, std::vector<Vector2>& pathList)
{
    while (goalNode) {
        pathList.emplace_back(goalNode->position);
        goalNode = goalNode->parent;
    }
}

inline float AStar::CalculteHeuristic(Node* currentNode, Node* goalNode)
{
    Vector2 diff = *currentNode - *goalNode;
    return diff.Magnitude();
}

inline bool AStar::IsInRange(int x, int y)
{
    return x >= 0 && y >= 0 && Engine::Get().GetScreenSize().GetX() > x && Engine::Get().GetScreenSize().GetY() > y;
}

inline bool AStar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}
