#include "Engine/Engine.h"
#include "Player.h"
#include "Math/Vector/Vector2.h"

Player::Player(char image) : Super(image)
{
	Engine::Get().SubscribeGetKeyDown(BINDFUNCTION(Player::MoveUp, Player), VK_UP);
	Engine::Get().SubscribeGetKeyDown(BINDFUNCTION(Player::MoveDown, Player), VK_DOWN);
	Engine::Get().SubscribeGetKeyDown(BINDFUNCTION(Player::MoveRight, Player), VK_RIGHT);
	Engine::Get().SubscribeGetKeyDown(BINDFUNCTION(Player::MoveLeft, Player), VK_LEFT);
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void Player::Destroy()
{
	Super::Destroy();
	Engine::Get().UnSubscribeGetKeyDown(BINDFUNCTION(Player::MoveUp, Player), VK_UP);
	Engine::Get().UnSubscribeGetKeyDown(BINDFUNCTION(Player::MoveDown, Player), VK_DOWN);
	Engine::Get().UnSubscribeGetKeyDown(BINDFUNCTION(Player::MoveRight, Player), VK_RIGHT);
	Engine::Get().UnSubscribeGetKeyDown(BINDFUNCTION(Player::MoveLeft, Player), VK_LEFT);
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
	if (newPosition.GetX() > 40) {
		newPosition = Vector2(0, newPosition.GetY());
	}

	SetPosition(newPosition);
}
