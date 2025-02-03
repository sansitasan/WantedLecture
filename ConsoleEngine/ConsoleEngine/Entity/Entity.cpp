#include "Engine/Engine.h"
#include "PreCompiledHeader.h"
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
	position = newPosition;
}
