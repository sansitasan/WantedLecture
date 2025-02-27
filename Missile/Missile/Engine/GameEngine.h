#pragma once
#include "Engine/Engine.h"

enum class ESceneType {
    StartScene,
    GameScene,
};

class GameEngine : public Engine {
public:
    GameEngine(int screenSizeX = 160, int screenSizeY = 90, int fontSizeX = 8, int fontSizeY = 8);
	virtual ~GameEngine() override;

	void ToggleMenu();

	static GameEngine* Get();
	void LoadScene(ESceneType sceneType = ESceneType::StartScene);

private:
	bool showMenu = false;
    static GameEngine* instance;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;
};