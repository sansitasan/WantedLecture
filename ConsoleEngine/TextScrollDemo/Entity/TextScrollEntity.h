#pragma once
#include "Entity/Entity.h"

class TextScrollEntity : public Entity
{
	enum class Direction {
		None = -1,
		Left = 0,
		Right = 1
	};

	RTTI_DECLARATIONS(TextScrollEntity, Entity)

public:
	TextScrollEntity(const char* message);
	~TextScrollEntity();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	void MoveLeft();
	void MoveRight();

private:
	Direction direction = Direction::None;

	bool shouldUpdate = false;
	float elapsedTime = 0;
	float delayTime = 0.125f;
	char* str = nullptr;
	int index = 0;
	int length = 0;

	static const int printWidth = 20;
};