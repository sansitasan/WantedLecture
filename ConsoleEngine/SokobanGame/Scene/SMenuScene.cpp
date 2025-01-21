#include "SMenuScene.h"
#include "Game/SGame.h"

SMenuScene::SMenuScene()
{
	items.emplace_back(new SMenuItem("Resume Game",
		[]()
		{
			SGame::Get().ToggleMenu();
		}));

	items.emplace_back(new SMenuItem("Quit Game",
		[]()
		{
			SGame::Get().QuitEngine();
		}));

	itemCount = (int)items.size();
}

SMenuScene::~SMenuScene()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unselectedColor);

	for (SMenuItem* item : items) {
		delete item;
	}
	items.clear();
}

void SMenuScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (SGame::Get().GetKey(VK_ESCAPE)) {
		SGame::Get().ToggleMenu();
	}

	if (SGame::Get().GetKey(VK_UP)) {
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	if (SGame::Get().GetKey(VK_DOWN)) {
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	if (SGame::Get().GetKey(VK_RETURN))
	{
		items[currentSelectedIndex]->onSelected();
	}
}

void SMenuScene::Draw()
{
	Super::Draw();

	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	Engine::Get().SetCursorPosition(Vector2::Zero);
	SetConsoleTextAttribute(handle, unselectedColor);

	std::cout << "TextScroll Demo Menu\n\n";

	for (int i = 0; i < itemCount; ++i) {
		SetConsoleTextAttribute(handle,
			i == currentSelectedIndex ? selectedColor : unselectedColor);

		std::cout << items[i]->text << '\n';
	}
}
