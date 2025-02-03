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

	virtual bool IsIntersect(const DrawableEntity& other);
	inline int GetWidth() const { return width; }

protected:
	char* image;

	//문자열 길이
	int width;

	Color entityColor = Color::White;

	unsigned int drawOrder = 0;
};