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
		//�޽�(�𵨸�) ������
		std::shared_ptr<class Mesh> mesh;
		//����޽� �� ��ŭ �ʿ�
		std::vector <std::weak_ptr<class Material>> materials;
	};
}