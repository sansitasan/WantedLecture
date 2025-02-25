#pragma once
#include <Scene/Scene.h>
#include <Memory/PlacePool.h>

struct Vector2; 
class GameScene : public Scene {
    RTTI_DECLARATIONS(GameScene, Scene)
public:
    GameScene();
    virtual ~GameScene();

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void GetPath(const Vector2& startPos, const Vector2& goalPos, std::vector<Vector2>& pathList);
private:
    PlacePool<DrawableEntity> entities;
    class AStar* aStar;
};