#pragma once
#include <Math/Vector/Vector2.h>
#include "RTTI.h"

class BlackBoard;

class INode {
public:
	INode() = default;
	INode(BlackBoard* blackBoard) : blackBoard(blackBoard) {};
	virtual ~INode() = 0;
	virtual bool CheckCondition() = 0;
	virtual void Update(float deltaTime) = 0;

protected:
	BlackBoard* blackBoard = nullptr;
};

inline INode::~INode() {}