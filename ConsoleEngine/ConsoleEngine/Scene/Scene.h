#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"

class Entity;

class ENGINE_API Scene : public RTTI
{
public:
	RTTI_DECLARATIONS(Scene, RTTI)

public:
	Scene();
	virtual ~Scene();

	void AddEntity(Entity* newEntity);
	//void DestroyEntity();

	void ProcessAddedAndDestroyedEntity();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	List<Entity*> SceneEntityList;

	Entity* addRequestedEntity = nullptr;
};

