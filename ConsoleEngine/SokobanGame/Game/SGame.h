#pragma once

#include "Engine/Engine.h"

class SGame : public Engine {
public:
	SGame();
	virtual ~SGame() override;

	void ToggleMenu();

	static SGame& Get() { return *instance; }

private:
	bool showMenu = false;

	Scene* menuScene = nullptr;
	Scene* backScene = nullptr;

	static SGame* instance;
};