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
		First = 60,
		Second = 19,
		Third = 19,
		Fourth = 2
	};

public:
	MoveNode() = default;
	MoveNode(BlackBoard* blackBoard);
	virtual ~MoveNode();
	virtual bool CheckCondition() override;
	virtual void Update(float deltaTime) override;
	virtual void Clear() override;

private:
	void SetDirRandomly();
	void SetMoveDir(int num);
	int RandomDir(const bool* canMove);
	EDir currentDir;
	Vector2 nextPos;
	short dir[4] = { 1, 2, 3, 2 };
};