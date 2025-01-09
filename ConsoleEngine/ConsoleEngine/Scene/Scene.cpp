#include "PreCompiledHeader.h"
#include "Scene.h"
#include "Entity/Entity.h"

Scene::Scene() {}

Scene::~Scene()
{
	for (int i = 0; i < SceneEntityList.Size(); ++i) {
		if (!SceneEntityList[i]) continue;
		SafeDelete(SceneEntityList[i]);
	}
}

void Scene::AddEntity(Entity* newEntity)
{
	SceneEntityList.PushBack(newEntity);
}

void Scene::DestroyEntity()
{
	//TODO: memmove to memcpy - index ����
	for (int i = 0; i < SceneEntityList.Size(); ++i) {
		if (!SceneEntityList[i]->IsExpired()) continue;
		delete SceneEntityList[i];
		SceneEntityList[i] = nullptr;
		SceneEntityList.Erase(i);
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
