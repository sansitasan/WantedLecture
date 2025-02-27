#pragma once
#include <Entity/DrawableEntity.h>

class Missile : public DrawableEntity {
	RTTI_DECLARATIONS(Missile, DrawableEntity)
public:
	Missile(const Vector2& position, std::wstring& str, class GameScene* scene);
    virtual ~Missile() = default;

    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    void Shoot();

private:
    class GameScene* scene;
    static const short speed = 5;
    bool doShoot = false;
    std::vector<Vector2> pathList;
    Vector2 tangentPoint0;
    Vector2 tangentPoint3;
};