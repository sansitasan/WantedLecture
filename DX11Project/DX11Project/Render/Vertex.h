#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace SanDX {
	class Vertex {
	public:
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord, const Vector3& normal)
			: position(position), color(color), texCoord(texCoord), normal(normal) { }

		static unsigned int Stride() { return sizeof(Vertex); }
	public:
		Vector3 position;
		Vector3 color;
		Vector3 normal;
		Vector2 texCoord;
	};
}