#include "StaticMeshComponent.h"
#include "Render/Mesh.h"
#include "Material/Material.h"
#include "Engine.h"

namespace SanDX {
	StaticMeshComponent::StaticMeshComponent()
	{
	}

	StaticMeshComponent::~StaticMeshComponent()
	{
	}

	void StaticMeshComponent::Draw()
	{
		uint32 size = mesh->SubMeshCount();

		if (size != materials.size()) return;

		for (uint32 i = 0; i < size; ++i) {
			auto subMesh = mesh->GetSubMesh(i);

			//메시가 없다?
			if (!subMesh.lock() || !materials[i].lock()) continue;

			subMesh.lock()->Bind();
			materials[i].lock()->Bind();
			Engine::Get().Context().DrawIndexed(subMesh.lock()->IndexCount(), 0u, 0u);
		}
	}

	void StaticMeshComponent::SetMesh(std::shared_ptr<class Mesh> newMesh)
	{
		mesh = newMesh;
	}

	void StaticMeshComponent::AddMaterial(std::weak_ptr<class Material> newMaterial)
	{
		materials.emplace_back(newMaterial);
	}
}