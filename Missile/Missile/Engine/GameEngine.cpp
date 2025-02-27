#include "GameEngine.h"
#include "Scene/StartScene.h"
#include "Scene/GameScene.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine(int screenSizeX, int screenSizeY, int fontSizeX, int fontSizeY)
	: Engine(screenSizeX, screenSizeY, fontSizeX, fontSizeY)
{
    if (instance) {
        delete this;
        return;
    }
    instance = this;
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(60);
	showMenu = false;
}

GameEngine::~GameEngine()
{
	if (showMenu) {
		SafeDelete(&backScene);
		backScene = nullptr;
	}

	else {
		SafeDelete(&mainScene);
	}

	SafeDelete(&menuScene);
}

void GameEngine::ToggleMenu()
{
	system("cls");

	showMenu = !showMenu;

	if (showMenu) {
		backScene = mainScene;
		mainScene = menuScene;
		return;
	}

	mainScene = backScene;
}

GameEngine* GameEngine::Get()
{
	return instance;
}

void GameEngine::LoadScene(ESceneType sceneType)
{
    if (mainScene) {
        SafeDelete(&mainScene);
    }
    switch (sceneType) {
    case ESceneType::StartScene:
        mainScene = TraceNew StartScene();
        break;

    case ESceneType::GameScene:
        mainScene = TraceNew GameScene();
        break;
    }
}
