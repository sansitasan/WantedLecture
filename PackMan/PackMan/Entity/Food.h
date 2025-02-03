#pragma once
#include <Entity/DrawableEntity.h>

class Food : public DrawableEntity {
	RTTI_DECLARATIONS(Food, DrawableEntity)
public:
	Food(const Vector2& position);
	virtual ~Food();

private:

};