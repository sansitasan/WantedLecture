#pragma once
#include <Scene/Scene.h>
#include <vector>
#include <Windows.h>

struct MenuItem {
	using OnSelected = void(*)();

	MenuItem(const char* text, OnSelected onSelected)
		:onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~MenuItem() {
		delete[] text;
		text = nullptr;
	}

	char* text;

	OnSelected onSelected;
};

class MenuScene : public Scene {
	RTTI_DECLARATIONS(MenuScene, Scene)

public:
	MenuScene();
	~MenuScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
private:
	int currentSelectedIndex = 0;

	int selectedColor = 
		FOREGROUND_GREEN | 
		FOREGROUND_INTENSITY;

	int unselectedColor = 
		FOREGROUND_RED | 
		FOREGROUND_GREEN | 
		FOREGROUND_BLUE | 
		FOREGROUND_INTENSITY;

	std::vector<MenuItem*> items;

	int itemCount = 0;
};