#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector/Vector2.h"
#include "PlayerBullet.h"

Player::Player(const char* image) : Super(image)
{
	position = Vector2(0, Engine::Get().GetScreenSize().GetY() - 1);
	KEYBIND(MoveUp, Player, VK_UP, KEYDOWN);
	KEYBIND(MoveDown, Player, VK_DOWN, KEYDOWN);
	KEYBIND(MoveRight, Player, VK_RIGHT, KEYDOWN);
	KEYBIND(MoveLeft, Player, VK_LEFT, KEYDOWN);
	KEYBIND(ShootBullet, Player, VK_SPACE, KEY);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Player::Destroy()
{
	Super::Destroy();
	int y = Engine::Get().GetScreenSize().GetY();
	Engine::Get().SetCursorPosition(position.GetX() - (width >> 1), y - 1);
	Log("  .  ");
	Engine::Get().SetCursorPosition(position.GetX() - (width >> 1), y);
	Log(".:V:.");

	Engine::Get().SetCursorPosition(position.GetX() - (width >> 1), y + 1);
	Log("GameOver!\n");

	KEYUNBIND(MoveUp, Player, VK_UP, KEYDOWN);
	KEYUNBIND(MoveDown, Player, VK_DOWN, KEYDOWN);
	KEYUNBIND(MoveRight, Player, VK_RIGHT, KEYDOWN);
	KEYUNBIND(MoveLeft, Player, VK_LEFT, KEYDOWN);
	KEYUNBIND(ShootBullet, Player, VK_SPACE, KEY);
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
	if (newPosition.GetY() > Engine::Get().GetScreenSize().GetY() - 1) {
		newPosition = Vector2(newPosition.GetX(), Engine::Get().GetScreenSize().GetY() - 1);
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
	if (newPosition.GetX() > Engine::Get().GetScreenSize().GetX() - width) {
		newPosition = Vector2(Engine::Get().GetScreenSize().GetX() - width, newPosition.GetY());
	}

	SetPosition(newPosition);
}

void Player::ShootBullet()
{
	Engine::Get().AddEntity(new PlayerBullet(position + Vector2(width >> 1, 0)));
}
