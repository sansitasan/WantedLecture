#include "PreCompiledHeader.h"
#include "Scene.h"
#include "Entity/Entity.h"

Scene::Scene()
	: SceneEntityList(nullptr), capacity(4), count(0)
{
	SceneEntityList = new Entity* [capacity];
	memset(SceneEntityList, 0, capacity * sizeof(Entity*));
}

Scene::~Scene()
{
	for (int i = 0; i < count; ++i) {
		if (!SceneEntityList[i]) continue;
		SafeDelete(SceneEntityList[i]);
	}
	delete[] SceneEntityList;
}

void Scene::AddEntity(Entity* newEntity)
{
	if (count == capacity) {
		capacity <<= 1;

		Entity** temp = new Entity * [capacity];

		memcpy(temp, SceneEntityList, count * sizeof(Entity*));

		delete[] SceneEntityList;
		SceneEntityList = temp;
	}

	SceneEntityList[count++] = newEntity;
}

void Scene::Update(float deltaTime)
{
	for (int i = 0; i < count; ++i) {
		SceneEntityList[i]->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (int i = 0; i < count; ++i) {
		SceneEntityList[i]->Draw();
	}
}
