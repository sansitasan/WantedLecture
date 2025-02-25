#include "GameScene.h"
#include <Engine/Engine.h>
#include <Entity/DrawableEntity.h>
#include "Astar/Astar.h"
#include "Entity/Missile.h"

GameScene::GameScene()
    : entities(1000), aStar(new AStar) 
{
    //for (int i = 0; i < 50; ++i) {
    //    AddEntity(&entities.MakeItem(Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()), Random(0, (int)Engine::Get().GetScreenSize().GetY())), std::wstring(TEXT("🚀"))));
    //}
    Vector2 x = Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()) >> 1, Random(0, (int)Engine::Get().GetScreenSize().GetY()));
    std::wstring y((TEXT("🚀")));
    AddEntity(new Missile(x, y, this));
    x = Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()) >> 1, Random(0, (int)Engine::Get().GetScreenSize().GetY()));
    AddEntity(new Missile(x, y, this));
    x = Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()) >> 1, Random(0, (int)Engine::Get().GetScreenSize().GetY()));
    AddEntity(new Missile(x, y, this));
}

GameScene::~GameScene() {}

void GameScene::Update(float deltaTime)
{
    Super::Update(deltaTime);
    //static float time = 0.f;
    //time += deltaTime;
    //
    //if (time < 1) return;
    //
    //time = 0;
}

void GameScene::Draw()
{
    Super::Draw();
    wchar_t buffer[256] = {};
    _snwprintf_s(buffer, sizeof(wchar_t) * 256, L"mousePos: %f, %f, FPS: %f", Engine::Get().GetMousePos().GetX(), Engine::Get().GetMousePos().GetY(),
        Engine::Get().GetFPS());
    Engine::Get().Draw(Vector2::Zero, buffer, Color::BrightWhite);
}

void GameScene::GetPath(const Vector2& startPos, const Vector2& goalPos, std::vector<Vector2>& pathList)
{
    aStar->Clear();
    aStar->FindPath(new Node((int)goalPos.GetX(), (int)goalPos.GetY()), new Node((int)startPos.GetX(), (int)startPos.GetY()), pathList);
}
