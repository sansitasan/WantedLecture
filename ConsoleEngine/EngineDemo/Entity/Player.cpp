#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector/Vector2.h"

Player::Player(const char* image) : Super(image)
{
	position = Vector2(0, 18);
	KEYBIND(MoveUp, Player, VK_UP);
	KEYBIND(MoveDown, Player, VK_DOWN);
	KEYBIND(MoveRight, Player, VK_RIGHT);
	KEYBIND(MoveLeft, Player, VK_LEFT);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Player::Destroy()
{
	Super::Destroy();
	KEYUNBIND(MoveUp, Player, VK_UP);
	KEYUNBIND(MoveDown, Player, VK_DOWN);
	KEYUNBIND(MoveRight, Player, VK_RIGHT);
	KEYUNBIND(MoveLeft, Player, VK_LEFT);
}

void Player::MoveUp()
{
	Vector2 newPosition = position;
	newPosition -= Vector2(0, 1);
	if (newPosition.GetY() < 0) {
		newPosition = Vector2(newPosition.GetX(), 0);
	}

	SetPosition(newPosition);
}

void Player::MoveDown()
{
	Vector2 newPosition = position;
	newPosition += Vector2(0, 1);
	if (newPosition.GetY() > 20) {
		newPosition = Vector2(newPosition.GetX(), 20);
	}

	SetPosition(newPosition);
}

void Player::MoveLeft()
{
	Vector2 newPosition = position;
	newPosition -= Vector2(1, 0);
	if (newPosition.GetX() < 0) {
		newPosition = Vector2(0, newPosition.GetY());
	}

	SetPosition(newPosition);
}

void Player::MoveRight()
{
	Vector2 newPosition = position;
	newPosition += Vector2(1, 0);
	if (newPosition.GetX() > 29) {
		newPosition = Vector2(29, newPosition.GetY());
	}

	SetPosition(newPosition);
}
