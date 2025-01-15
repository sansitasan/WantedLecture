#pragma once
#include <Entity/DrawableEntity.h>

class Target : public DrawableEntity
{
	RTTI_DECLARATIONS(Target, DrawableEntity)

public:
	Target(const Vector2& position);

private:
};