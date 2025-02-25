#include "StartScene.h"
#include "Engine/GameEngine.h"

StartScene::StartScene()
{
    title = std::vector<std::wstring>(7);
    title[0] = TEXT("##   ##  ######    #####    #####   ######   ##       #######");
    title[1] = TEXT("##   ##    ##     ##   ##  ##   ##    ##     ##       ##");
    title[2] = TEXT("### ###    ##     ##       ##         ##     ##       ##");
    title[3] = TEXT("## # ##    ##      #####    #####     ##     ##       #####");
    title[4] = TEXT("## # ##    ##          ##       ##    ##     ##       ##");
    title[5] = TEXT("##   ##    ##     ##   ##  ##   ##    ##     ##       ##");
    title[6] = TEXT("##   ##  ######    #####    #####   ######   ######   #######");

    std::vector<std::wstring> start(5);
    start[0] = TEXT(" ##   #              #         ##");
    start[1] = TEXT("#    ###   #   ##   ###       #     #   ###   ##");
    start[2] = TEXT(" #    #   # #  # #   #        # #  # #  ###  ###");
    start[3] = TEXT("  #   #   # #  #     #        # #  # #  ###  #");
    start[4] = TEXT("##    #    ##  #     #         ##   ##  # #   ##");

    Vector2 itemPos((Engine::Get().GetScreenSize().GetX() - start[2].size()) * 0.5f, Engine::Get().GetScreenSize().GetY() * 0.5f);
    items.emplace_back(TraceNew MenuItem(itemPos, std::move(start),
        []()
        {
            GameEngine::Get().LoadScene(ESceneType::GameScene);
        }));

    std::vector<std::wstring> quit(5);
    quit[0] = TEXT(" #         #    #         ##");
    quit[1] = TEXT("# #  # #       ###       #     #   ###   ##");
    quit[2] = TEXT("# #  # #   #    #        # #  # #  ###  ###");
    quit[3] = TEXT("##   # #   #    #        # #  # #  ###  #");
    quit[4] = TEXT(" ##  ###   #    #         ##   ##  # #   ##");

    itemPos.SetX((Engine::Get().GetScreenSize().GetX() - quit[2].size()) * 0.5f);
    itemPos += Vector2(0, 7);

    items.emplace_back(TraceNew MenuItem(itemPos, std::move(quit),
        []()
        {
            GameEngine::Get().QuitEngine();
        }));

    itemCount = (int)items.size();
}

StartScene::~StartScene()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (int)unselectedColor);

	for (MenuItem* item : items) {
		delete item;
	}
	items.clear();
}

void StartScene::Update(float deltaTime)
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

void StartScene::Draw()
{
	Super::Draw();

	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (int)unselectedColor);
	Vector2 size = Engine::Get().GetScreenSize();
    for (int i = 0; i < (int)title.size(); ++i) {
        Engine::Get().Draw(Vector2((size.GetX() - title[3].size()) * 0.5f, 3.f + i), title[i], unselectedColor);
    }

	for (int i = 0; i < itemCount; ++i) {
		items[i]->Draw(i == currentSelectedIndex ? selectedColor : unselectedColor);
	}
}

void MenuItem::Draw(Color color)
{
    Vector2 temp;
    for (int i = 0; i < text.size(); ++i) {
        temp = position + Vector2(0, i);
        Engine::Get().Draw(temp, text[i], color);
    }
}
