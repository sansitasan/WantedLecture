#pragma once
#include "Core.h"

class BlackBoard;
class Entity;
class INode;
class IMoveable;
class GameScene;

class BehaviorTree {
public:
	BehaviorTree(Entity* entity, IMoveable* target, GameScene* scene);
	~BehaviorTree();
	void AddNode(INode& node);
	void Update(float deltaTime);
	BlackBoard* GetBlackBoard();
private:
	std::vector<INode*> nodes;
	BlackBoard* blackBoard;
};