#pragma once
#include "Scene/Scene.h"
#include <Math/Vector/Vector2.h>

class DrawableEntity;
class SPlayer;
class Box;
class Target;
class Ground;

class GameScene : public Scene
{
	RTTI_DECLARATIONS(GameScene, Scene)

public:
	GameScene();
	virtual ~GameScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	bool CanPlayerMove(const Vector2& position);

private:
	bool IsGameClear();

private:
	int moveCount = 0;
	bool isClear = false;

	List<DrawableEntity*> map;
	List<Box*> boxes;
	List<Target*> targets;
	SPlayer* player = nullptr;
};

