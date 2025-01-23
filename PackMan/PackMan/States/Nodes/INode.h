#pragma once
#include <Math/Vector/Vector2.h>
#include "RTTI.h"

class BlackBoard;

class INode {
public:
	enum class ENodeStates {
		None,
		Run,
		Stop
	};
public:
	INode() = default;
	INode(BlackBoard* blackBoard) : blackBoard(blackBoard) {};
	virtual ~INode() = 0;
	virtual bool CheckCondition() = 0;
	virtual void Update(float deltaTime) = 0;
	ENodeStates GetNodeState() const { return nodeStates; }
	virtual void Clear() = 0;

protected:
	BlackBoard* blackBoard = nullptr;
	ENodeStates nodeStates = ENodeStates::Stop;
};

inline INode::~INode() {}