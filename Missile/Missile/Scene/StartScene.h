#pragma once
#include <Scene/Scene.h>
#include <Math/Vector/Vector2.h>

struct MenuItem {
	using OnSelected = void(*)();

	MenuItem(const Vector2& position, std::vector<std::wstring>&& text, OnSelected onSelected)
		:onSelected(onSelected), text(text), position(position) { }

    void Draw(Color color);

	~MenuItem() = default;

    Vector2 position;
	std::vector<std::wstring> text;
	OnSelected onSelected;
};

class StartScene : public Scene {
	RTTI_DECLARATIONS(StartScene, Scene)
public:
	StartScene();
	virtual ~StartScene();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentSelectedIndex = 0;
	int itemCount = 0;
	Color selectedColor = Color::BrightGreen;
	Color unselectedColor = Color::BrightWhite;
    std::vector<std::wstring> title;
	std::vector<MenuItem*> items;
};