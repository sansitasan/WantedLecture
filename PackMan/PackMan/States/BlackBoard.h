#pragma once

class Entity;
class IMoveable;
class GameScene;

class BlackBoard {
public:
	BlackBoard(Entity* entity, IMoveable* target, GameScene* scene)
		: entity(entity), target(target), scene(scene) {}

	~BlackBoard() {
		entity = nullptr;
		target = nullptr;
		scene = nullptr;
	}

	Entity* entity;
	IMoveable* target;
	GameScene* scene;
};