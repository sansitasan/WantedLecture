#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Container/List.h"
#include <queue>

class Entity;
class DrawableEntity;

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
	bool IsActive() const { return isActiveScene; }

	void AddDeleteEntityQueue(Entity* expiredEntity);

protected:
	void ChangedActive(bool isActive);

protected:
	List<Entity*> SceneEntityList;
	//List<DrawableEntity*> drawableEntityList;

	bool isActiveScene = true;

	std::queue<Entity*> addRequestedEntityQueue;
	std::queue<Entity*> deleteRequestedEntityQueue;
};

