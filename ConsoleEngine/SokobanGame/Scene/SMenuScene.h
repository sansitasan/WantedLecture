#pragma once
#include <Scene/Scene.h>
#include <vector>
#include <Windows.h>

struct SMenuItem {
	using OnSelected = void(*)();

	SMenuItem(const char* text, OnSelected onSelected)
		:onSelected(onSelected) {
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}

	~SMenuItem() {
		delete[] text;
		text = nullptr;
	}

	char* text;

	OnSelected onSelected;
};

class SMenuScene : public Scene {
	RTTI_DECLARATIONS(SMenuScene, Scene)

public:
	SMenuScene();
	~SMenuScene();

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

	std::vector<SMenuItem*> items;

	int itemCount = 0;
};