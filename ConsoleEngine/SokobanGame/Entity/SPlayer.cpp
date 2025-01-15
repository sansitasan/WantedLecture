#include "SPlayer.h"
#include "Scene/GameScene.h"
#include "Engine/Engine.h"

SPlayer::SPlayer(const Vector2& position, GameScene* gameScene)
	: Super("p"), gameScene(gameScene)
{
	this->position = position;
	KEYBIND(MoveUp, SPlayer, VK_UP, KEY);
	KEYBIND(MoveDown, SPlayer, VK_DOWN, KEY);
	KEYBIND(MoveRight, SPlayer, VK_RIGHT, KEY);
	KEYBIND(MoveLeft, SPlayer, VK_LEFT, KEY);
}

void SPlayer::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void SPlayer::MoveUp() {
	Vector2 newPosition = position - Vector2(0, 1);
	if (gameScene->CanPlayerMove(newPosition)) {
		SetPosition(newPosition);
	}
}

void SPlayer::MoveDown()
{
	Vector2 newPosition = position + Vector2(0, 1);
	if (gameScene->CanPlayerMove(newPosition)) {
		SetPosition(newPosition);
	}
}

void SPlayer::MoveLeft()
{
	Vector2 newPosition = position - Vector2(1, 0);
	if (gameScene->CanPlayerMove(newPosition)) {
		SetPosition(newPosition);
	}
}

void SPlayer::MoveRight()
{
	Vector2 newPosition = position + Vector2(1, 0);
	if (gameScene->CanPlayerMove(newPosition)) {
		SetPosition(newPosition);
	}
}
