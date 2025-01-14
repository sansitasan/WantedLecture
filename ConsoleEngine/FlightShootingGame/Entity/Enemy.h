#pragma once
#include <Entity/DrawableEntity.h>

class Enemy : public DrawableEntity
{
	RTTI_DECLARATIONS(Enemy, DrawableEntity)

public:
	Enemy(const char* image, int yPosition);

	virtual void Update(float deltaTime) override;
private:
	float speed = 5.0f;
	float xPosition = 5.0f;

	float elapsedTime = 0.f;
	float moveTime;
};

