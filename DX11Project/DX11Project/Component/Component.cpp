#include "Component.h"
#include "Entity/Entity.h"

namespace SanDX
{
    Component::Component()
    {
    }

    Component::~Component()
    {
    }

    void Component::BeginPlay()
    {
    }

    void Component::Update(float deltaTime)
    {
    }

    void Component::Draw()
    {
    }

    Entity* Component::GetOwner() const
    {
        return owner;
    }

    void Component::SetOwner(Entity* newOwner)
    {
        owner = newOwner;
    }
}