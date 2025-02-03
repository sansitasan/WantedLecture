#pragma once
#include <Entity/DrawableEntity.h>

class Wall : public DrawableEntity {
	RTTI_DECLARATIONS(Wall, DrawableEntity)
public:
	Wall(const Vector2& position) 
		: DrawableEntity("X", true)
	{
		this->position = position;
		entityColor = Color::Intensity;
	};

private:
};