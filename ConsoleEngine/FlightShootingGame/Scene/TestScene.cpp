#include "TestScene.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Entity/Player.h"
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
}
