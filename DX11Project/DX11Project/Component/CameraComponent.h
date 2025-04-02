#pragma once
#include "Component.h"
#include "Math/Matrix4x4.h"
#include <d3d11.h>

namespace SanDX {
	//ī�޶� ���� (��� ����) �� ����� �Ѱ���� ��
	struct CameraBuffer {
		Matrix4x4 viewMatrix;
	};

	class CameraComponent : public Component {
	public:
		CameraComponent();
		~CameraComponent() = default;

		virtual void Draw() override;

	private:
		bool isPerspective = true;

		CameraBuffer cameraBuffer;

		ID3D11Buffer* buffer = nullptr;
	};
}