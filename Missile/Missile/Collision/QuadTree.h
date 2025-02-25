#pragma once
#include "Core.h"

struct Vector2;
class QuadNode;

class QuadTree {
public:
    QuadTree(const Vector2& screenSize);
    ~QuadTree();

    void insert(const Vector2& player);

    void Remove();

    bool IsMouseNear(const Vector2& otherPosition, Vector2& playerPosition);

public:
    static const int maxDepth = 4;

private:
    QuadNode* root = nullptr;
};