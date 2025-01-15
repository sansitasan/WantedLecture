#pragma once
#include <Entity/DrawableEntity.h>

class EnemyBullet : public DrawableEntity
{
	RTTI_DECLARATIONS(EnemyBullet, DrawableEntity)

public:
	EnemyBullet(const Vector2& position);

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

private:
	float speed = 7.5f;
	float yPosition = 0;
};

