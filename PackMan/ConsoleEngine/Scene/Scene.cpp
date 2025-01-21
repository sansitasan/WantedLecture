#include "PreCompiledHeader.h"
#include "Scene.h"
#include "Entity/DrawableEntity.h"

Scene::Scene() {
}

Scene::~Scene()
{
	for (int i = 0; i < SceneEntityList.Size(); ++i) {
		if (!SceneEntityList[i]) continue;
		SafeDelete(&SceneEntityList[i]);
	}

	while (!deleteRequestedEntityQueue.empty()) {
		delete deleteRequestedEntityQueue.front();
		deleteRequestedEntityQueue.pop();
	}

	while (!addRequestedEntityQueue.empty()) {
		delete addRequestedEntityQueue.front();
		addRequestedEntityQueue.pop();
	}
}

void Scene::AddEntity(Entity* newEntity)
{	
	addRequestedEntityQueue.push(newEntity);
}

void Scene::ProcessAddedAndDestroyedEntity()
{
	while (!deleteRequestedEntityQueue.empty()) {
		delete deleteRequestedEntityQueue.front();
		deleteRequestedEntityQueue.pop();
	}

	while (!addRequestedEntityQueue.empty()) {
		SceneEntityList.PushBack(addRequestedEntityQueue.front());
		addRequestedEntityQueue.pop();
	}
}

void Scene::Update(float deltaTime)
{
	for (Entity* entity : SceneEntityList) {
		if (entity->IsExpired() || !entity->IsActive()) continue;
		entity->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (Entity* entity : SceneEntityList) {
		if (entity->IsExpired() || !entity->IsActive()) continue;
		entity->Draw();
	}
}

void Scene::AddDeleteEntityQueue(Entity* expiredEntity)
{
	if (!expiredEntity->IsExpired()) return;
	deleteRequestedEntityQueue.push(expiredEntity);
	for (int i = 0; i < SceneEntityList.Size();) {
		if (SceneEntityList[i]->GetUniqueID() != expiredEntity->GetUniqueID()) {
			++i;
			continue;
		}

		SceneEntityList.Erase(i);
	}
}

void Scene::ChangedActive(bool isActive)
{
	isActiveScene = isActive;
	for (Entity* entity : SceneEntityList) {
		entity->SetActive(isActive);
	}
}
