#pragma once
#include "Scene/Scene.h"

class TestScene : public Scene
{
	RTTI_DECLARATIONS(TestScene, Scene)

public:
	TestScene();
	virtual ~TestScene() override;

	virtual void Update(float deltaTime) override;

private:
	void SpawnEnemy(float deltaTime);

	void ProcessCollisionPlayerBulletAndEnemy();
	void ProcessCollisionEnemyBulletAndPlayer();

private:
	int score = 0;
};

