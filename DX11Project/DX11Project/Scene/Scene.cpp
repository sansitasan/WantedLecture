#include "Scene.h"
#include "Entity/Entity.h"
#include "Component/CameraComponent.h"

namespace SanDX {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::BeginPlay()
	{
		//중간에 추가되는 엔티티를 위해 돌린다
		//비긴플레이가 시작되지 않은 큐 혹은 리스트를 만들어서 처리하는 편이 좋을 듯
		for (const auto& entity : entities) {
			entity->BeginPlay();
		}
	}

	void Scene::Update(float deltaTime)
	{
		if (camera) camera->Update(deltaTime);

		for (const auto& entity : entities) {
			entity->Update(deltaTime);
		}
	}

	void Scene::AddEntity(std::shared_ptr<Entity> newEntity)
	{
		for (auto& component : newEntity->components) {
			CameraComponent* isCamera = dynamic_cast<CameraComponent*>(component.get());
			if (isCamera) {
				camera = newEntity;
				return;
			}
		}
		entities.emplace_back(newEntity);
	}
	std::shared_ptr<Entity> Scene::GetCamera()
	{
		return camera;
	}
}