#include "MenuScene.h"
#include "Engine/GameEngine.h"

MenuScene::MenuScene()
{
	items.emplace_back(TraceNew MenuItem("Resume Game",
		[]()
		{
			GameEngine::Get().ToggleMenu();
		}));

	items.emplace_back(TraceNew MenuItem("Quit Game",
		[]()
		{
			GameEngine::Get().QuitEngine();
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

	if (GameEngine::Get().GetKey(VK_ESCAPE)) {
		GameEngine::Get().ToggleMenu();
	}

	if (GameEngine::Get().GetKey(VK_UP)) {
		currentSelectedIndex = (currentSelectedIndex - 1 + itemCount) % itemCount;
	}

	if (GameEngine::Get().GetKey(VK_DOWN)) {
		currentSelectedIndex = (currentSelectedIndex + 1) % itemCount;
	}

	if (GameEngine::Get().GetKey(VK_RETURN))
	{
		items[currentSelectedIndex]->onSelected();
	}
}

void MenuScene::Draw()
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
