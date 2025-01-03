#include "TestScene.h"
#include "Engine/Engine.h"
#include <Windows.h>

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE)) {
		Engine::Get().QuitEngine();
	}
}
