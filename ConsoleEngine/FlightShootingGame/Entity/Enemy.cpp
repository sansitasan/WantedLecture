#include "Engine/Engine.h"
#include "Enemy.h"
#include "EnemyBullet.h"

const char* Enemy::enemyType[] = {
		";(^);",
		"zZTZz",
		"oO&Oo",
		"<=-=>",
		")~O~(",
		"[[0]]"
};

Enemy::Enemy()
	: DrawableEntity(enemyType[Random(0, _countof(enemyType) - 1)])
{
	this->position = Vector2(Random((width >> 1) + 1, Engine::Get().GetScreenSize().GetX() - (width >> 1)), Random(1, 15));
	moveTime = RandomPercent(1, 3);
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Shoot(deltaTime);

	Move(deltaTime);
}

void Enemy::Move(float deltaTime)
{
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

void Enemy::Shoot(float deltaTime)
{
	static float elapsedTime = 0;
	static float shootInterval = RandomPercent(1, 2);

	elapsedTime += deltaTime;

	if (elapsedTime < shootInterval) return;

	elapsedTime = 0;
	shootInterval = RandomPercent(1, 2);

	Engine::Get().AddEntity(new EnemyBullet(Vector2(position.GetX() + (width >> 1), position.GetY())));
}
