#include "DemoScene.h"

#include "Entity/QuadEntity.h"
#include "Entity/SphereEntity.h"
#include "Entity/CameraEntity.h"

#include "Render/QuadMesh.h"

#include "Resource/MaterialLoader.h"
#include "Resource/ModelLoader.h"
#include "Resource/TextureLoader.h"

#include "Material/TextureMappingMaterial.h"

#include "Component/StaticMeshComponent.h"

#include "Math/Transform.h"
#include "Component/CameraComponent.h"

namespace SanDX {
	DemoScene::DemoScene()
	{
		std::shared_ptr<SphereEntity> entity = std::make_shared<SphereEntity>();
		AddEntity(entity);

		std::shared_ptr<QuadEntity> entity2 = std::make_shared<QuadEntity>();
		entity2->transform.position.x += 2.f;
		AddEntity(entity2);

		std::shared_ptr<QuadEntity> entity3 = std::make_shared<QuadEntity>();
		entity3->transform.position.x += 4.f;
		AddEntity(entity3);

		std::shared_ptr<CameraEntity> cameraEntity = std::make_shared<CameraEntity>();
		cameraEntity->transform.position.z -= 2;
		cameraEntity->AddComponent(std::make_shared<CameraComponent>());

		AddEntity(cameraEntity);
	}

	DemoScene::~DemoScene()
	{
	}
}