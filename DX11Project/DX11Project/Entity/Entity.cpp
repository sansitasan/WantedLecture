#include "Entity.h"
#include "Component/Component.h"

namespace SanDX {
	Entity::Entity()
	{
	}

	Entity::~Entity()
	{
	}

	void Entity::BeginPlay()
	{
		if (HasInitialized()) return;

		hasInitialized = true;

		for (const auto& component : components) {
			component->BeginPlay();
		}
	}

	void Entity::Update(float deltaTime)
	{
		if (!IsActive()) return;

		transform.Update();

		for (const auto& component : components) {
			component->Update(deltaTime);
		}
	}

	void Entity::Draw()
	{
		transform.Bind();

		if (!IsActive()) return;

		for (const auto& component : components) {
			component->Draw();
		}
	}

	void Entity::AddComponent(std::shared_ptr<class Component> newComponent)
	{
		components.emplace_back(newComponent);

		newComponent->SetOwner(this);
	}
}