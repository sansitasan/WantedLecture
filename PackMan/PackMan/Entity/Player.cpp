#include "Player.h"
#include "Engine/GameEngine.h"
#include "Entity/Item.h"
#include "Scene/GameScene.h"

Player::Player(const Vector2& position, GameScene* gameScene)
	:Super("P"), currentSpeed(6), originSpeed(6), moveDir(Vector2::Zero), gameScene(gameScene), currentState(EState::Normal)
{
	this->position = position;
	entityColor = Color::BrightGreen;
	KEYBIND(MoveUp, Player, VK_UP, KEY);
	KEYBIND(MoveDown, Player, VK_DOWN, KEY);
	KEYBIND(MoveLeft, Player, VK_LEFT, KEY);
	KEYBIND(MoveRight, Player, VK_RIGHT, KEY);
}

void Player::Update(float deltaTime)
{
	Vector2 newPos = position + moveDir * deltaTime * currentSpeed;
	if (gameScene->CanMove(newPos, this)) {
		SetPosition(newPos);
	}
}

void Player::Draw()
{
	Super::Draw();
}

void Player::Destroy()
{
	Super::Destroy();
}

EState Player::GetState() const
{
	return currentState;
}

Vector2 Player::GetPosition() const
{
	return Super::GetPosition();
}

void Player::GetItem(Item& item)
{
	if (item.UseItem(*this)) {
		++itemCount;
		currentState = EState::Super;
		currentSpeed = originSpeed * 1.5f;
		COROUTINE(SetStateOrigin, Player, 3, false);
	}
}

void Player::MoveUp()
{
	moveDir = Vector2::Down;
}

void Player::MoveDown()
{
	moveDir = Vector2::Up;
}

void Player::MoveLeft()
{
	moveDir = Vector2::Left;
}

void Player::MoveRight()
{
	moveDir = Vector2::Right;
}

void Player::SetStateOrigin()
{
	--itemCount;
	if (itemCount) return;
	currentSpeed = static_cast<float>(originSpeed);
	currentState = EState::Normal;
}
