#include "QuadEntity.h"
#include "Component/StaticMeshComponent.h"
#include "Render/QuadMesh.h"
#include "Material/TextureMappingMaterial.h"
#include "Resource/MaterialLoader.h"

namespace SanDX {
	QuadEntity::QuadEntity()
	{
		std::shared_ptr<StaticMeshComponent> meshComponent = std::make_shared<StaticMeshComponent>();

		AddComponent(meshComponent);

		meshComponent->SetMesh(std::make_shared<QuadMesh>());
		std::weak_ptr<TextureMappingMaterial> material;
		if (MaterialLoader::Get().Load<TextureMappingMaterial>(material, "head_face_M_BC.png")) {
			meshComponent->AddMaterial(material);
		}
	}
}