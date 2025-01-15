#pragma once

#include <Entity/DrawableEntity.h>

class PlayerBullet : public DrawableEntity {
	RTTI_DECLARATIONS(PlayerBullet, DrawableEntity)

public:
	//탄약 생성 시 위치 전달받기
	PlayerBullet(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:
	float speed = 20.0f;

	float yPosition = 0.f;
};