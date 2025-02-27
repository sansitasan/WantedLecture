#include "QuadTree.h"
#include "QuadNode.h"

QuadTree::QuadTree(const Vector2& screenSize)
{
    root = new QuadNode(Bound(Vector2::Zero, screenSize));
}

QuadTree::~QuadTree()
{
    SafeDelete(&root);
}

void QuadTree::insert(const Vector2& player)
{
    root->Insert(player);
}

void QuadTree::Remove()
{
    root->Remove();
}

bool QuadTree::IsMouseNear(const Vector2& otherPosition, Vector2& playerPosition)
{
    return root->IsMouseNear(otherPosition, playerPosition);
}

void QuadTree::Draw(unsigned short executeLayer)
{
    root->Draw(executeLayer);
}
