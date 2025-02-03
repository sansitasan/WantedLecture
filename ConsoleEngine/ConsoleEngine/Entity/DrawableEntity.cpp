#include "PreCompiledHeader.h"
#include "Engine/Engine.h"
#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(const char* image, unsigned int drawOrder)
	: Entity(), drawOrder(drawOrder), width((int)strlen(image))
{
	size_t length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);
}

DrawableEntity::~DrawableEntity()
{
	delete[] image;
}

void DrawableEntity::Draw()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)entityColor);
	Engine::Get().SetCursorPosition(position);
	Log(image);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)Color::White);
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
