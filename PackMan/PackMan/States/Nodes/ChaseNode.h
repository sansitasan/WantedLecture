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
	virtual void Clear() override;

private:
	bool Check(Vector2 searchedPos, const Vector2& dir, const Vector2& targetPos, int depth);
private:
	bool IsInBoundary();
	int depth = 3;
};