#include "GameEngine.h"
#include "Scene/GameScene.h"
#include "Scene/MenuScene.h"
#include "Manager/DataManager.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine()
{
	if (instance != nullptr) {
		delete this;
		return;
	}

	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(60);
	instance = this;
	menuScene = TraceNew MenuScene();
	showMenu = false;
	dataManager = new DataManager();
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
	SafeDelete(&dataManager);
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

void GameEngine::LoadGameScene()
{
	mainScene = new GameScene(*dataManager);
}
