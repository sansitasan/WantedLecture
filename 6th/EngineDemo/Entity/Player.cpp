#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector/Vector2.h"

Player::Player(char image) : Super(image)
{
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LEFT)) {
		Vector2 newPosition = position;
		newPosition -= Vector2(1, 0);
		if (newPosition.GetX() < 0) {
			newPosition = Vector2(0, newPosition.GetY());
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT)) {
		Vector2 newPosition = position;
		newPosition += Vector2(1, 0);
		if (newPosition.GetX() > 40) {
			newPosition = Vector2(40, newPosition.GetY());
		}

		SetPosition(newPosition);
	}
}
