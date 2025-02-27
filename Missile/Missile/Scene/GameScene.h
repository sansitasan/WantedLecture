#pragma once
#include <Scene/Scene.h>
#include <Memory/PlacePool.h>
#include "Core.h"
#include "Entity/Missile.h"

struct Vector2;
class GameScene : public Scene {
    RTTI_DECLARATIONS(GameScene, Scene)
public:
    GameScene();
    virtual ~GameScene();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    bool GetPath(const Vector2& startPos, Vector2& goalPos, std::vector<Vector2>& pathList);
    unsigned short GetExecuteLayer() const { return executeLayer; }

private:
    FORCEINLINE void LayerUpdate();

private:
    PlacePool<Missile> entities;
    class AStar* aStar;
    class QuadTree* quadTree;

    unsigned short executeLayer = 0;
    unsigned short curveLayer = 0;
};