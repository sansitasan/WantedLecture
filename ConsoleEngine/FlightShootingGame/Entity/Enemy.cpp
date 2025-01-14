#include "Engine/Engine.h"
#include "Enemy.h"

Enemy::Enemy(const char* image, int yPosition)
	: DrawableEntity(image)
{
	this->position = Vector2(0, yPosition);
	moveTime = RandomPercent(1, 3);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	elapsedTime += deltaTime;

	if (elapsedTime < moveTime) return;

	elapsedTime = 0;
	moveTime = RandomPercent(1, 3);

	position += RandomPercent() < 0.5f ? Vector2(1, 0) : Vector2(-1, 0);
	if (position.GetX() > Engine::Get().GetScreenSize().GetX()) {
		position = Vector2(Engine::Get().GetScreenSize().GetX(), position.GetY());
	}

	else if (position.GetX() < 1) {
		position = Vector2(1, position.GetY());
	}
}
