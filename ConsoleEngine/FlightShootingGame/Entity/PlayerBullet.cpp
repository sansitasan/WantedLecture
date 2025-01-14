#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: DrawableEntity("!")
{
	this->position = position;
	yPosition = position.GetY();
}

void PlayerBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	position -= Vector2(0, speed * deltaTime);

	if (position.GetY() < 0.f) {
		Destroy();
		return;
	}
}
