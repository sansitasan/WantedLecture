#pragma once
#include "INode.h"


class CollisionNode : public INode, public RTTI
{
	RTTI_DECLARATIONS(CollisionNode, RTTI)

public:
	CollisionNode() = default;
	CollisionNode(BlackBoard* blackBoard);
	virtual ~CollisionNode();
	virtual bool CheckCondition() override;
	virtual void Update(float deltaTime) override;

private:
};