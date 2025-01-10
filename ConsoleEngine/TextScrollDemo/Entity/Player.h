#pragma once
#include "Entity/DrawableEntity.h"

class Player : public DrawableEntity
{
	RTTI_DECLARATIONS(Player, DrawableEntity)

public:
	Player(char image = 'P');

	virtual void Update(float deltaTime) override;
};

