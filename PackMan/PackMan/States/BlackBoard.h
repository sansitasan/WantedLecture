#pragma once
#include <Math/Vector/Vector2.h>

class DrawableEntity;
class IMoveable;
class GameScene;

class BlackBoard {
public:
	BlackBoard(DrawableEntity* entity, IMoveable* target, GameScene* scene, float speed)
		: entity(entity), target(target), scene(scene), dir(Vector2::Left), speed(speed) {}

	~BlackBoard() {
		entity = nullptr;
		target = nullptr;
		scene = nullptr;
	}

	DrawableEntity* entity;
	IMoveable* target;
	GameScene* scene;
	Vector2 dir;
	float speed;
};