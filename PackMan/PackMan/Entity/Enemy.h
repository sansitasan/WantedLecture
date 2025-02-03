#pragma once
#include <Entity/DrawableEntity.h>

class GameScene;
class BehaviorTree;
class IMoveable;

class Enemy : public DrawableEntity {
	RTTI_DECLARATIONS(Enemy, DrawableEntity)
public:
	Enemy(const Vector2& position, GameScene* gameScene, IMoveable* player);
	virtual ~Enemy();

	virtual void Update(float deltaTime) override;
	Vector2 GetSpawnPoint() const;
private:
	void MakeBT();

private:
	GameScene* gameScene;
	Vector2 spawnPosition;
	BehaviorTree* bt;
};