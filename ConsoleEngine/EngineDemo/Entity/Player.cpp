#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector/Vector2.h"

Player::Player(const char* image) : Super(image)
{
	position = Vector2(MAXX, MAXY);
	KEYBIND(MoveUp, Player, VK_UP, KEYDOWN);
	KEYBIND(MoveDown, Player, VK_DOWN, KEYDOWN);
	KEYBIND(MoveRight, Player, VK_RIGHT, KEYDOWN);
	KEYBIND(MoveLeft, Player, VK_LEFT, KEYDOWN);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Player::Destroy()
{
	Super::Destroy();
	KEYUNBIND(MoveUp, Player, VK_UP, KEYDOWN);
	KEYUNBIND(MoveDown, Player, VK_DOWN, KEYDOWN);
	KEYUNBIND(MoveRight, Player, VK_RIGHT, KEYDOWN);
	KEYUNBIND(MoveLeft, Player, VK_LEFT, KEYDOWN);
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
	if (newPosition.GetY() > MAXY) {
		newPosition = Vector2(newPosition.GetX(), MAXY);
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
	if (newPosition.GetX() > MAXX) {
		newPosition = Vector2(MAXX, newPosition.GetY());
	}

	SetPosition(newPosition);
}
