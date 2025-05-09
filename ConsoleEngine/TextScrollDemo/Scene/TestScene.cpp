#include "TestScene.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Entity/Player.h"
#include "Entity/TextScrollEntity.h"
#include "Game/Game.h"
#include <Windows.h>

TestScene::TestScene()
{
	//AddEntity(new Player('a'));
	AddEntity(new TextScrollEntity("San Sensei Teach me Rap!!"));
}

TestScene::~TestScene()
{
}

void TestScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKey(VK_ESCAPE)) {
		//Engine::Get().QuitEngine();
		Game::Get().ToggleMenu();
	}
}
