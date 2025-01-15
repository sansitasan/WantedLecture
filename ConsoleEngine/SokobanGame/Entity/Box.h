#pragma once
#include <Entity/DrawableEntity.h>

class Box : public DrawableEntity
{
	RTTI_DECLARATIONS(Box, DrawableEntity)

public:
	Box(const Vector2& position);

private:
};