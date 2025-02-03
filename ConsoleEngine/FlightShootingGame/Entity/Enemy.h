#pragma once
#include <Entity/DrawableEntity.h>

class Enemy : public DrawableEntity
{
	RTTI_DECLARATIONS(Enemy, DrawableEntity)

public:
	Enemy();

	virtual void Update(float deltaTime) override;

	void Move(float deltaTime);

private:
	void Shoot(float deltaTime);

private:
	static const char* enemyType[];
	float speed = 5.0f;
	float xPosition = 5.0f;

	float elapsedTime = 0.f;
	float moveTime;
};

