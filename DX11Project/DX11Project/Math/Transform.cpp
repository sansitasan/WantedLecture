#include "Transform.h"

namespace SanDX {
	Transform::Transform()
	{
	}

	Transform::Transform(const Matrix4x4& matrix)
		: transformMatrix(matrix)
	{
	}

	Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
		: position(position), rotation(rotation), scale(scale)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Bind()
	{
	}
}