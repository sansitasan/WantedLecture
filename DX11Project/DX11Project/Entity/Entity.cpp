#include "Entity.h"

namespace SanDX {
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::BeginPlay()
	{
		hasInitialized = true;
	}

	void Entity::Update(float deltaTime)
	{
	}

	void Entity::Draw()
	{
		transform.Bind();
	}
}