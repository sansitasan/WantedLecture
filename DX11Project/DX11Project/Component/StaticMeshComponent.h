#pragma once
#include "Component.h"
#include <memory>
#include <vector>

namespace SanDX {
	class StaticMeshComponent : public Component {
	public:
		StaticMeshComponent();
		~StaticMeshComponent();

		virtual void Draw() override;

		void SetMesh(std::shared_ptr<class Mesh> newMesh);

		void AddMaterial(std::weak_ptr<class Material> newMaterial);

	private:
		//메시(모델링) 데이터
		std::shared_ptr<class Mesh> mesh;
		//서브메시 수 만큼 필요
		std::vector <std::weak_ptr<class Material>> materials;
	};
}