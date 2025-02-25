#pragma once
#include "Engine/Engine.h"

enum class ESceneType {
    StartScene,
    GameScene,
};

class GameEngine : public Engine {
public:
	virtual ~GameEngine() override;

	void ToggleMenu();

	static GameEngine& Get(int screenSizeX = 160, int screenSizeY = 90, int fontSizeX = 8, int fontSizeY = 8);
	void LoadScene(ESceneType sceneType = ESceneType::StartScene);

private:
	GameEngine(int screenSizeX = 160, int screenSizeY = 90, int fontSizeX = 4, int fontSizeY = 4);
	bool showMenu = false;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;
};