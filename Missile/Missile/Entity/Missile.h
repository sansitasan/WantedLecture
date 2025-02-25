#pragma once
#include <Entity/DrawableEntity.h>

class Missile : public DrawableEntity {
	RTTI_DECLARATIONS(Missile, DrawableEntity)
public:
	Missile(const Vector2& position, std::wstring& str, class GameScene* scene);
    virtual ~Missile() = default;

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

private:
    Vector2 mousePos;
    class GameScene* scene;
    //float speed;
    std::vector<Vector2> pathList;
};