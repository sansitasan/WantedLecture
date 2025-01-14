#include "TestScene.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include <Windows.h>

TestScene::TestScene()
{
	AddEntity(new Player("<P>"));
}

TestScene::~TestScene()
{
}

void TestScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE)) {
		Engine::Get().QuitEngine();
	}

	static float elapsedTime = 0.f;
	static float spawnTime = RandomPercent(1, 3);

	elapsedTime += deltaTime;
	if (elapsedTime < spawnTime) return;

	elapsedTime = 0;

	AddEntity(new Enemy("[@]", Random(1, 15)));
}
