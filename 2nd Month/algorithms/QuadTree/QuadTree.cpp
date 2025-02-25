#include "QuadTree.h"

QuadTree::QuadTree(const Bound& bound)
{
    root = new Node(bound);
}

QuadTree::~QuadTree()
{
    SafeDelete(root);
}

void QuadTree::Insert(Node* node)
{
    root->Insert(node);
}

std::vector<Node*> QuadTree::Query(Node* queryNode)
{
    std::vector<Node*> possibleNodes;
    root->Query(queryNode->GetBound(), possibleNodes);

    std::vector<Node*> intersects;

    for (Node* node : possibleNodes) {
        for (Node* point : node->Points()) {
            if (point->GetBound().Intersects(queryNode->GetBound())) {
                intersects.emplace_back(point);
                continue;
            }
        }

    }
    return intersects;
}
