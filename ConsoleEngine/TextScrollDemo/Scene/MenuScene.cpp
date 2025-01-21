#include "MenuScene.h"
#include "Game/Game.h"

MenuScene::MenuScene()
{
	items.emplace_back(new MenuItem("Resume Game", 
		[]() 
		{
			Game::Get().ToggleMenu();
		}));

	items.emplace_back(new MenuItem("Quit Game", 
		[]() 
		{ 
			Game::Get().QuitEngine(); 
		}));

	itemCount = (int)items.size();
}

MenuScene::~MenuScene()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unselectedColor);

	for (MenuItem* item : items) {
		delete item;
	}
	items.clear();
}

void MenuScene::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Game::Get().GetKey(VK_ESCAPE)) {
		Game::Get().ToggleMenu();
	}

	if (Game::Get().GetKey(VK_UP)) {
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	if (Game::Get().GetKey(VK_DOWN)) {
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	if (Game::Get().GetKey(VK_RETURN))
	{
		items[currentSelectedIndex]->onSelected();
	}
}

void MenuScene::Draw()
{
	Super::Draw();

	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, unselectedColor);

	std::cout << "TextScroll Demo Menu\n\n";

	for (int i = 0; i < itemCount; ++i) {
		SetConsoleTextAttribute(handle,
			i == currentSelectedIndex ? selectedColor : unselectedColor);

		std::cout << items[i]->text << '\n';
	}
}
