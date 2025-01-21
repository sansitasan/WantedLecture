#pragma once
#include "INode.h"

class MoveNode : public INode, public RTTI
{
	RTTI_DECLARATIONS(MoveNode, RTTI)

private:
	enum class EDir {
		Left,
		Up,
		Right,
		Down
	};

	enum class ERand {
		First = 33,
		Second = 33,
		Third = 33,
		Fourth = 1
	};

public:
	MoveNode() = default;
	MoveNode(BlackBoard* blackBoard);
	virtual ~MoveNode();
	virtual bool CheckCondition() override;
	virtual void Update(float deltaTime) override;

private:
	void SetDirRandomly();
	void SetMoveDir(int num);
	int RandomDir(const bool* canMove);
	float speed = 5;
	EDir currentDir;
	Vector2 moveDir;
	Vector2 nextPos;
	short dir[4] = { 1, 2, 3, 2 };
};