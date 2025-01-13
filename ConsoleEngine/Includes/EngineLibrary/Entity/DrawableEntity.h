#pragma once
#include "Entity.h"

class ENGINE_API DrawableEntity : public Entity
{
public:
	RTTI_DECLARATIONS(DrawableEntity, Entity)

public:
	DrawableEntity(const char* image, unsigned int drawOrder = 0);
	virtual ~DrawableEntity();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;
protected:
	char* image;

	unsigned int drawOrder = 0;
};

