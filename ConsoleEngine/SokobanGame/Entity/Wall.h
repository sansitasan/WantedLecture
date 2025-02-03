#pragma once
#include <Entity/DrawableEntity.h>

class Wall : public DrawableEntity {
	RTTI_DECLARATIONS(Wall, DrawableEntity)

public:
	Wall(const Vector2& position);

private:

};