#include "BT.h"
#include "BlackBoard.h"
#include "Nodes/INode.h"
#include "Scene/GameScene.h"
#include "IMoveable.h"

BehaviorTree::BehaviorTree(DrawableEntity* entity, IMoveable* target, GameScene* scene, float entitySpeed)
{
	blackBoard = new BlackBoard(entity, target, scene, entitySpeed);
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
	int idx = 1;
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i]->CheckCondition()) {
			idx += i;
			nodes[i]->Update(deltaTime);
			break;
		}
	}

	for (int i = idx; i < nodes.size(); ++i) {
		if (nodes[i]->GetNodeState() != INode::ENodeStates::Run) continue;
		nodes[i]->Clear();
	}
}

BlackBoard* BehaviorTree::GetBlackBoard()
{
	return blackBoard;
}
