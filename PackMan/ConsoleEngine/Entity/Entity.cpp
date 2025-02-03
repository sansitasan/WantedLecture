#include "PreCompiledHeader.h"
#include "Engine/Engine.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::Update(float deltaTime)
{

}

void Entity::Draw()
{
}

inline Vector2 Entity::GetPosition() const
{
	return position;
}

void Entity::SetPosition(const Vector2& newPosition)
{
	Vector2 pos = newPosition;
	if (newPosition.GetX() > Engine::Get().GetScreenSize().GetX()) {
		pos = Vector2(Engine::Get().GetScreenSize().GetX() - 1, newPosition.GetY());
	}

	if (newPosition.GetX() < 0) {
		pos = Vector2(0.f, newPosition.GetY());
	}

	if (newPosition.GetY() > Engine::Get().GetScreenSize().GetY()) {
		pos = Vector2(newPosition.GetX(), Engine::Get().GetScreenSize().GetY() - 1);
	}

	if (newPosition.GetY() < 0) {
		pos = Vector2(newPosition.GetX(), 0.f);
	}

	position = newPosition;
}
