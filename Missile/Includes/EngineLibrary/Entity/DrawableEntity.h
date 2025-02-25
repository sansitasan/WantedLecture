#pragma once
#include "Entity.h"

class ENGINE_API DrawableEntity : public Entity
{
public:
	RTTI_DECLARATIONS(DrawableEntity, Entity)

public:
	DrawableEntity(const Vector2& position, std::wstring& image, unsigned int drawOrder = 0, bool isStaticDraw = false);
	virtual ~DrawableEntity();

	virtual void Draw() override;
	virtual void SetPosition(const Vector2& newPosition) override;
	inline void SetColor(Color newColor) { entityColor = newColor; }

	virtual bool IsIntersect(const DrawableEntity& other);
	inline short GetWidth() const { return width; }
	inline bool IsStaticDraw() const { return isStaticDraw; }
	inline std::wstring GetImage() const { return image; }

protected:
	std::wstring image;

	//문자열 길이
	short width;

	Color entityColor = Color::White;
    bool isStaticDraw;

    unsigned int drawOrder = 0;
};