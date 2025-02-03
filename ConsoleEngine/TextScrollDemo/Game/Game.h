#pragma once

#include "Engine/Engine.h"

class Game : public Engine {
public:
	Game();
	virtual ~Game() override;

	void ToggleMenu();

	static Game& Get() { return *instance; }

private:
	bool showMenu = false;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;

	static Game* instance;
};