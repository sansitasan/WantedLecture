#include "GameEngine.h"
#include "Scene/GameScene.h"
#include "Scene/MenuScene.h"
#include "Manager/DataManager.h"


GameEngine::GameEngine(int screenSizeX, int screenSizeY, int fontSizeX, int fontSizeY)
	: Engine(screenSizeX, screenSizeY, fontSizeX, fontSizeY)
{
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(60);
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

GameEngine& GameEngine::Get(int screenSizeX, int screenSizeY, int fontSizeX, int fontSizeY)
{
	static GameEngine instance = GameEngine(screenSizeX, screenSizeY, fontSizeX, fontSizeY);
	return instance;
}

void GameEngine::LoadGameScene()
{
	mainScene = new GameScene(*dataManager);
}
