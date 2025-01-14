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
	Super::Draw();
	Engine::Get().SetCursorPosition(position);

	Log(image);
}

void DrawableEntity::SetPosition(const Vector2& newPosition)
{
	//Engine::Get().SetCursorPosition(position);
	//Log(" ");
	Super::SetPosition(newPosition);
}
