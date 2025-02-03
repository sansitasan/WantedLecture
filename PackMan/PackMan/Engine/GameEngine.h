#pragma once
#include "Engine/Engine.h"

class DataManager;

class GameEngine : public Engine {
public:
	GameEngine();
	virtual ~GameEngine() override;

	void ToggleMenu();

	static GameEngine& Get() { return *instance; }
	void LoadGameScene();


private:
	bool showMenu = false;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;

	static GameEngine* instance;
	DataManager* dataManager;
};