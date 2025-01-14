#include "Game.h"
#include "Scene/MenuScene.h"

Game* Game::instance = nullptr;

Game::Game() : Engine()
{
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(60);
	instance = this;
	menuScene = new MenuScene();
	showMenu = false;
}

Game::~Game()
{
	if (showMenu) {
		delete backScene;
		backScene = nullptr;
		mainScene = nullptr;
	}

	else {
		delete mainScene;
		mainScene = nullptr;
	}

	delete menuScene;
	menuScene = nullptr;
}

void Game::ToggleMenu()
{
	//ȭ�� �����
	system("cls");

	showMenu = !showMenu;

	if (showMenu) {
		backScene = mainScene;
		mainScene = menuScene;
		return;
	}

	mainScene = backScene;
}
