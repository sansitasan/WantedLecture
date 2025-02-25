#include "Missile.h"
#include <Engine/Engine.h>
#include "Scene/GameScene.h"

Missile::Missile(const Vector2& position, std::wstring& str, class GameScene* scene)
	: Super(position, str), scene(scene), mousePos(0, 0)
{
}

void Missile::Update(float deltaTime)
{
    Super::Update(deltaTime);
    if (Engine::Get().GetKey(VK_LBUTTON)) {
        position = Vector2(Random(0, (int)Engine::Get().GetScreenSize().GetX()) >> 1, Random(0, (int)Engine::Get().GetScreenSize().GetY()));
    }
}

void Missile::Draw()
{
    Super::Draw();
    if (mousePos != Engine::Get().GetMousePos()) {
        mousePos = Engine::Get().GetMousePos();
        pathList.clear();
        scene->GetPath(position, mousePos, pathList);
    }

    for (int i = 1; i < pathList.size(); ++i) {
        Engine::Get().Draw(pathList[i], TEXT("x"), Color::BrightRed);
    }
}