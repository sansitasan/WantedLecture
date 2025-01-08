#include "PreCompiledHeader.h"
#include "Engine/Engine.h"
#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(char image)
	: Entity(), image(image) {}

void DrawableEntity::Draw()
{
	Super::Draw();
	Engine::Get().SetCursorPosition(position);

	Log("%c", image);
}

void DrawableEntity::SetPosition(const Vector2& newPosition)
{
	Engine::Get().SetCursorPosition(position);
	Log(" ");
	Super::SetPosition(newPosition);
}
