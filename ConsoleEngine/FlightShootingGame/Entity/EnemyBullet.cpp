#include "EnemyBullet.h"
#include "Engine/Engine.h"
#include <Windows.h>

EnemyBullet::EnemyBullet(const Vector2& position)
	:Super(".")
{
	this->position = position;
	yPosition = position.GetY();
}

void EnemyBullet::Update(float deltaTime)
{
	Super::Update(deltaTime);

	yPosition += speed * deltaTime;
	position += Vector2(0, speed * deltaTime);
	if (position.GetY() >= Engine::Get().GetScreenSize().GetY()) {
		Destroy();
	}
}

void EnemyBullet::Draw()
{
	Super::Draw();
}
