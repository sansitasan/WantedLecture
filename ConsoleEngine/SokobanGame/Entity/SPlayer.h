#pragma once
#include <Entity/DrawableEntity.h>

class GameScene;

class SPlayer : public DrawableEntity
{
	RTTI_DECLARATIONS(SPlayer, DrawableEntity)

public:
	SPlayer(const Vector2& position, GameScene* gameScene);

	virtual void Update(float deltaTime) override;

private:
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private:
	GameScene* gameScene;
};