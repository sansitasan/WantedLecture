#pragma once

#include <Entity/DrawableEntity.h>

class PlayerBullet : public DrawableEntity {
	RTTI_DECLARATIONS(PlayerBullet, DrawableEntity)

public:
	//ź�� ���� �� ��ġ ���޹ޱ�
	PlayerBullet(const Vector2& position);

	virtual void Update(float deltaTime) override;

private:
	float speed = 20.0f;

	float yPosition = 0.f;
};