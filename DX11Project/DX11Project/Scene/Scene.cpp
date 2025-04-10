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
		//�߰��� �߰��Ǵ� ��ƼƼ�� ���� ������
		//����÷��̰� ���۵��� ���� ť Ȥ�� ����Ʈ�� ���� ó���ϴ� ���� ���� ��
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