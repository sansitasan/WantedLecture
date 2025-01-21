#pragma once
#include "INode.h"


class ChaseNode : public INode, public RTTI
{
	RTTI_DECLARATIONS(ChaseNode, RTTI)

public:
	ChaseNode() = default;
	ChaseNode(BlackBoard* blackBoard);
	virtual ~ChaseNode();
	virtual bool CheckCondition() override;
	virtual void Update(float deltaTime) override;

private:
	bool IsInBoundary();
	Vector2 min;
	Vector2 max;
};