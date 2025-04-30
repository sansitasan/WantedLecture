#include "SphereEntity.h"
#include "Component/StaticMeshComponent.h"
#include "Render/SphereMesh.h"
#include "Material/TextureMappingMaterial.h"
#include "Material/NormalMappingMaterial.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"
#include "Render/Texture.h"

namespace SanDX {
	SphereEntity::SphereEntity()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();

		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<SphereMesh>());
		std::weak_ptr<NormalMappingMaterial> material;
		if (MaterialLoader::Get().Load<NormalMappingMaterial>(material)) {
			using ETextureBindType = NormalMappingMaterial::ETextureBindType;
			meshComponent->AddMaterial(material);

			std::weak_ptr<Texture> texture;
			TextureLoader::Get().Load("5k_earth_day_map.png", texture);
			//material.lock()->SetTexture(texture);
			material.lock()->SetTexture(ETextureBindType::Diffuse, texture);
			TextureLoader::Get().Load("8k_earth_normal_map.png", texture);
			material.lock()->SetTexture(ETextureBindType::NormalMap, texture);
		}
	}
	void SphereEntity::Update(float deltaTime)
	{
		Entity::Update(deltaTime);
		transform.rotation.y += deltaTime * 10.f;
	}
}