#pragma once
#include <Entity/DrawableEntity.h>

class Ground : public DrawableEntity {
	RTTI_DECLARATIONS(Ground, DrawableEntity)

public:
	Ground(const Vector2& position);

private:

};