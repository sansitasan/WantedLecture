#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"
#include <d3d11.h>

namespace SanDX {
	class Transform {
	public:
		Transform();
		Transform(const Matrix4x4& matrix);
		Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
		~Transform();

		void Update();
		void Bind();

	public:
		Vector3 position = Vector3::Zero;
		Vector3 rotation = Vector3::Zero;
		Vector3 scale = Vector3::One;

	private:
		Matrix4x4 transformMatrix;
		ID3D11Buffer* constantBuffer = nullptr;
	};
}