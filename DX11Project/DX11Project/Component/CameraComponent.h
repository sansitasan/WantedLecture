#pragma once
#include "Component.h"
#include "Math/Matrix4x4.h"
#include <d3d11.h>

namespace SanDX {
	//카메라 버퍼 (상수 버퍼) 뷰 행렬을 넘겨줘야 함
	struct alignas(16) CameraBuffer {
		Matrix4x4 viewMatrix;

		Matrix4x4 projectionMatrix;

		Vector3 cameraPosition;

		float padding;
	};

	class CameraComponent : public Component {
	public:
		CameraComponent();
		~CameraComponent() = default;

		virtual void Draw() override;

	private:
		CameraBuffer cameraBuffer;

		ID3D11Buffer* buffer = nullptr;

		bool isPerspective = true;
	};
}