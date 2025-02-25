#pragma once
#include "Engine/Engine.h"

class DataManager;

class GameEngine : public Engine {
public:
	virtual ~GameEngine() override;

	void ToggleMenu();

	static GameEngine& Get(int screenSizeX = 35, int screenSizeY = 40, int fontSizeX = 16, int fontSizeY = 16);
	void LoadGameScene();

private:
	GameEngine(int screenSizeX = 35, int screenSizeY = 40, int fontSizeX = 16, int fontSizeY = 16);
	bool showMenu = false;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;
	DataManager* dataManager;
};