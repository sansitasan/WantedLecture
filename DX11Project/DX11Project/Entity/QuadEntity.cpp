#include "QuadEntity.h"
#include "Component/StaticMeshComponent.h"
#include "Render/QuadMesh.h"
#include "Render/SphereMesh.h"
#include "Material/TextureMappingMaterial.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"
#include "Render/Texture.h"

namespace SanDX {
	QuadEntity::QuadEntity()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();

		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<SphereMesh>());
		std::weak_ptr<TextureMappingMaterial> material;
		if (MaterialLoader::Get().Load<TextureMappingMaterial>(material)) {
			meshComponent->AddMaterial(material);

			std::weak_ptr<Texture> texture;
			TextureLoader::Get().Load("head_face_M_BC.png", texture);
			material.lock()->SetTexture(texture);
		}
	}
}