#pragma once
#include "Core.h"

class BlackBoard;
class DrawableEntity;
class INode;
class IMoveable;
class GameScene;

class BehaviorTree {
public:
	BehaviorTree(DrawableEntity* entity, IMoveable* target, GameScene* scene, float entitySpeed);
	~BehaviorTree();
	void AddNode(INode& node);
	void Update(float deltaTime);
	BlackBoard* GetBlackBoard();
private:
	std::vector<INode*> nodes;
	BlackBoard* blackBoard;
};