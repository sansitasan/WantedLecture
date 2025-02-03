#pragma once
#include "Entity/DrawableEntity.h"

class Player : public DrawableEntity
{
	RTTI_DECLARATIONS(Player, DrawableEntity)

public:
	Player(const char* image);
	
	virtual void Update(float deltaTime) override;
	
	virtual void Destroy() override;
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShootBullet();
};

