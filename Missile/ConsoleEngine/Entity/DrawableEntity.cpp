#include "PreCompiledHeader.h"
#include "Engine/Engine.h"
#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(const Vector2& position, std::wstring& image, unsigned int drawOrder, bool isStaticDraw)
	: Entity(position), drawOrder(drawOrder), width((int)image.size()), isStaticDraw(isStaticDraw), image(image)
{
}

DrawableEntity::~DrawableEntity()
{
}

void DrawableEntity::Draw()
{
	Engine::Get().Draw(Vector2((int)position.GetX(), (int)position.GetY() + 1), image, entityColor);
}

void DrawableEntity::SetPosition(const Vector2& newPosition)
{
	Super::SetPosition(newPosition);
}

bool DrawableEntity::IsIntersect(const DrawableEntity& other)
{
	int min = (int)position.GetX();
	int max = (int)position.GetX() + width;

	int otherMin = (int)other.position.GetX();
	int otherMax = (int)other.position.GetX() + other.width;

	if (otherMin > max || otherMax < min) return false;

	return (int)position.GetY() == (int)other.position.GetY();
}
