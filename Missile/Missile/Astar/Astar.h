#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <Math/Vector/Vector2.h>

//오늘의 찐빠
//Set의 Compare에서 같다고 판정된 원소는 추가되지 않는다.
//소수라고 해도 같다고 판정되는 원소는 존재할 수 있다.
//따라서 조건을 추가해야 한다.
class Node {
public:
    inline Node(int x, int y, Node* parent = nullptr)
        : position(x, y), parent(parent) {
    }

    inline ~Node() = default;

    inline Vector2 operator-(const Node& other) {
        return Vector2(position - other.position);
    }

    inline Vector2 operator+(const Node& other) {
        return Vector2(position + other.position);
    }

    inline bool operator==(const Node& other) const {
        return position.IntCompare(other.position);
    }

    inline bool operator!=(const Node& other) const {
        return !position.IntCompare(other.position);
    }

public:
    Vector2 position;

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
    AStar() = default;
    ~AStar();

    //경로 검색 함수
    bool FindPath(
        Node* startNode,
        Node* goalNode,
        std::vector<Vector2>& pathList);

    void Clear();

private:
    //최적 경로 반환 함수
    //목표노드에서 부모 노드 역추적
    inline void ConstructPath(Node* goalNode, std::vector<Vector2>& pathList);

    //hCost 계산 함수
    inline float CalculteHeuristic(Node* currentNode, Node* goalNode);

    //탐색 위치가 범위 내에 있는지
    inline bool IsInRange(int x, int y);

    //탐색 위치가 목표 위치인지 확인
    inline bool IsDestination(const Node* node);
private:
    struct Compare {
        bool operator()(const Node* a, const Node* b) const {
            return a->fCost > b->fCost;
        }
    };

    struct NodeEqual {
        bool operator()(const Node* a, const Node* b) const {
            return *a == *b;
        }
    };

    struct NodeHash {
        size_t operator()(const Node* node) const {
            return std::hash<float>()(node->position.GetX()) ^ std::hash<float>()(node->position.GetY());
        }
    };

    std::priority_queue<Node*, std::vector<Node*>, Compare> openQ;
    std::unordered_set<Node*, NodeHash, NodeEqual> closedSet;
    Node* startNode = nullptr;
    Node* goalNode = nullptr;
};