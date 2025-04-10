#include "DemoScene.h"

#include "Entity/QuadEntity.h"

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
		std::shared_ptr<QuadEntity> entity = std::make_shared<QuadEntity>();
		AddEntity(entity);

		std::shared_ptr<Entity> cameraEntity = std::make_shared<Entity>();
		cameraEntity->AddComponent(std::make_shared<CameraComponent>());

		AddEntity(cameraEntity);
	}

	DemoScene::~DemoScene()
	{
	}
}