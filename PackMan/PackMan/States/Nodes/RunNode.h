#pragma once
#include "INode.h"


class RunNode : public INode, public RTTI
{
	RTTI_DECLARATIONS(RunNode, RTTI)

public:
	RunNode() = default;
	RunNode(BlackBoard* blackBoard);
	virtual ~RunNode();
	virtual bool CheckCondition() override;
	virtual void Update(float deltaTime) override;
	virtual void Clear() override;

private:
	inline void FindRoute(const Vector2& targetPos, const Vector2& originPos);
	inline void SetnextPos(const Vector2& targetPos, Vector2 nearPos, const Vector2& dir, int& max);
	inline int CheckManhattanDistance(const Vector2& targetPos, const Vector2& comparePos);
	Vector2 nextPos;
	float originSpeed;
};