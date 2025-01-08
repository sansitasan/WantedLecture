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

void Scene::Update(float deltaTime)
{
	for (Entity* entity : SceneEntityList) {
		entity->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (Entity* entity : SceneEntityList) {
		entity->Draw();
	}
}
