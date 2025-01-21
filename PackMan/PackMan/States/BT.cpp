#include "BT.h"
#include "BlackBoard.h"
#include "Nodes/INode.h"
#include "Scene/GameScene.h"
#include "IMoveable.h"

BehaviorTree::BehaviorTree(Entity* entity, IMoveable* target, GameScene* scene)
{
	blackBoard = new BlackBoard(entity, target, scene);
}

BehaviorTree::~BehaviorTree()
{
	for (int i = 0; i < nodes.size(); ++i) {
		delete nodes[i];
	}
	nodes.clear();
	SafeDelete(&blackBoard);
}

void BehaviorTree::AddNode(INode& node)
{
	nodes.push_back(&node);
}

void BehaviorTree::Update(float deltaTime)
{
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i]->CheckCondition()) {
			nodes[i]->Update(deltaTime);
			break;
		}
	}
}

BlackBoard* BehaviorTree::GetBlackBoard()
{
	return blackBoard;
}
