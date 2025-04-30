#include "QuadEntity.h"
#include "Component/StaticMeshComponent.h"
#include "Render/QuadMesh.h"
#include "Material/TextureMappingMaterial.h"
#include "Material/NormalMappingMaterial.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"
#include "Render/RenderTexture.h"

namespace SanDX {
	QuadEntity::QuadEntity()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();

		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<QuadMesh>());
		std::weak_ptr<TextureMappingMaterial> material;
		if (MaterialLoader::Get().Load<TextureMappingMaterial>(material)) {
			meshComponent->AddMaterial(material);

			std::weak_ptr<RenderTexture> renderTexture;
			TextureLoader::Get().MakeRenderTexture(renderTexture, 1280, 800);
			material.lock()->SetTexture(renderTexture);
		}
	}
	void QuadEntity::Update(float deltaTime)
	{
		Entity::Update(deltaTime);
	}
}