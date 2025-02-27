#include "Missile.h"
#include <Engine/Engine.h>
#include "Scene/GameScene.h"
#include "Curve/BézierCurve.h"
#include <Math/Matrix/Matrix2x2.h>

Missile::Missile(const Vector2& position, std::wstring& str, class GameScene* scene)
	: Super(position, str), scene(scene), tangentPoint0(0, 0), tangentPoint3(0, 0)
{
}

//S = V * T
//T = S / V
void Missile::Update(float deltaTime)
{
    Super::Update(deltaTime);
    if (scene->GetExecuteLayer() & (unsigned short)EExecuteLayer::BézierCurve) {
        //Shoot();
    }
}

void Missile::Draw()
{
    Super::Draw();
    pathList.clear();
    Vector2 result(-1, -1);

    if (scene->GetPath(position, result, pathList) && scene->GetExecuteLayer() & (unsigned short)EExecuteLayer::AStarDraw) {
        for (int i = 1; i < pathList.size(); ++i) {
            Engine::Get().Draw(pathList[i], TEXT("x"), Color::BrightRed);
        }
    }

    if (scene->GetExecuteLayer() & (unsigned short)EExecuteLayer::BézierCurve) {
        Vector2 mousePosition = Engine::Get().GetMousePos();
        float t = speed / (mousePosition - position).Magnitude();

        tangentPoint0 = Rotate(Matrix2x2::Rad45, mousePosition - position);
        tangentPoint3 = Rotate(Matrix2x2::Rad180, Rotate(Matrix2x2::Rad45, position - mousePosition));
        Vector2 temp;

        for (float i = t; i < 1; i += t) {
            GetPointHermite(position, mousePosition, i, temp,
                tangentPoint0, tangentPoint3);
            Engine::Get().Draw(temp, TEXT("o"), Color::BrightRed);
        }
    }
}

void Missile::Shoot()
{
    Vector2 mousePosition = Engine::Get().GetMousePos();
    float t = speed / (mousePosition - position).Magnitude();
    t = t > 1 ? 1 : t;

    if (!doShoot) {
        tangentPoint0 = Rotate(Matrix2x2::Rad30, mousePosition - position);
        tangentPoint3 = Rotate(Matrix2x2::Rad30, position - mousePosition);
        doShoot = true;
    }

    if (t == 1) doShoot = false;
    GetPointHermite(position, mousePosition, t, position, 
        tangentPoint0, tangentPoint3);
}
