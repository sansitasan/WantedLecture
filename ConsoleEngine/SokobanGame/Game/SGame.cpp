#include "SGame.h"
#include "Scene/SMenuScene.h"

SGame* SGame::instance = nullptr;

SGame::SGame() : Engine()
{
	SetCursorType(ECursorType::NoCursor);
	SetTargetFrameRate(60);
	instance = this;
	menuScene = new SMenuScene();
	showMenu = false;
}

SGame::~SGame()
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

void SGame::ToggleMenu()
{
	//화면 지우기
	system("cls");

	showMenu = !showMenu;

	if (showMenu) {
		backScene = mainScene;
		mainScene = menuScene;
		return;
	}

	mainScene = backScene;
}
