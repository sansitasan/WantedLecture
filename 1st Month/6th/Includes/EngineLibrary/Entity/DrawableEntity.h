#pragma once
#include "Entity.h"

class ENGINE_API DrawableEntity : public Entity
{
public:
	RTTI_DECLARATIONS(DrawableEntity, Entity)

public:
	DrawableEntity(char image = ' ');
	virtual ~DrawableEntity() = default;

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;
protected:
	char image;
};

