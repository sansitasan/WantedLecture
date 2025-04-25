#include "GameScene.h"
#include <Engine/Engine.h>
#include <Entity/DrawableEntity.h>
#include "Astar/Astar.h"
//#include "Entity/Missile.h"
#include "Collision/QuadTree.h"

GameScene::GameScene()
    : entities(1000), aStar(TraceNew AStar), quadTree(TraceNew QuadTree(Engine::Get().GetScreenSize()))
{
    std::wstring x(TEXT("🚀"));
    for (int i = 0; i < 25; ++i) {
        SceneEntityList.push_back(&entities.MakeItem(Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()), Random(0, (int)Engine::Get().GetScreenSize().GetY())), x, this));
    }
}

GameScene::~GameScene() {
    SafeDelete(&aStar);
    SafeDelete(&quadTree);
}

void GameScene::Update(float deltaTime)
{
    Super::Update(deltaTime);
    LayerUpdate();

    if (Engine::Get().GetKey(VK_LBUTTON)) {
        quadTree->Remove();
        quadTree->insert(Engine::Get().GetMousePos());
    }

    //static float time = 0.f;
    //time += deltaTime;
    //
    //if (time < 1) return;
    //
    //time = 0;
    //AddEntity(&entities.MakeItem(Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()), Random(0, (int)Engine::Get().GetScreenSize().GetY())), std::wstring(TEXT("🚀")), this));
}

void GameScene::Draw()
{
    if (executeLayer & (short)EExecuteLayer::QuadTreeDraw) {
        quadTree->Draw(executeLayer);
    }

    Super::Draw();

    wchar_t buffer[255] = {};
    _snwprintf_s(buffer, 255, L"mousePos: %d, %d | FPS: %f | Mode: %u", 
        (int)Engine::Get().GetMousePos().GetX(), (int)Engine::Get().GetMousePos().GetY(),
        Engine::Get().GetFPS(),
        executeLayer);
    Engine::Get().Draw(Vector2::Zero, buffer, Color::BrightWhite);
    //OutputDebugString(buffer);
    //if (_heapchk() != _HEAPOK)
    //{
    //    __debugbreak();
    //}
}

bool GameScene::GetPath(const Vector2& startPos, Vector2& goalPos, std::vector<Vector2>& pathList)
{
    if (!(executeLayer & (short)EExecuteLayer::AStarExecute)) return false;

    if (executeLayer & (short)EExecuteLayer::QuadTree) {
        if (!quadTree->IsMouseNear(startPos, goalPos)) return false;
    }
    else goalPos = Engine::Get().GetMousePos();

    aStar->Clear();
    aStar->FindPath(TraceNew Node((int)goalPos.GetX(), (int)goalPos.GetY()), TraceNew Node((int)startPos.GetX(), (int)startPos.GetY()), pathList);
    return !pathList.empty();
}

FORCEINLINE void GameScene::LayerUpdate()
{
    if (Engine::Get().GetKey(VK_F1))
        executeLayer ^= (short)EExecuteLayer::QuadTree;

    if (Engine::Get().GetKey(VK_F2))
        executeLayer ^= (short)EExecuteLayer::QuadTreeDraw;

    if (Engine::Get().GetKey(VK_F3))
        executeLayer ^= (short)EExecuteLayer::QuadTreePositionDraw;

    if (Engine::Get().GetKey(VK_F4))
        executeLayer ^= (short)EExecuteLayer::AStarExecute;

    if (Engine::Get().GetKey(VK_F5))
        executeLayer ^= (short)EExecuteLayer::AStarDraw;

    if (Engine::Get().GetKey(VK_F6))
        executeLayer ^= (short)EExecuteLayer::BézierCurve;
}
