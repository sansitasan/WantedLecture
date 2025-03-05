#pragma once
#include "../Math/Vector3.h"
#include "../Math/Vector2.h"

namespace SanDX {
	class Vertex {
		struct float2 {

			float2(float x, float y)
				: x(x), y(y) {
			}

			float2(const Vector2& vector)
				: x(vector.GetX()), y(vector.GetY()) {
			}

			float x;
			float y;
		};
	public:
		Vertex(const Vector3& position, const Vector3& color, const Vector2& texCoord, const Vector3& normal)
			: position(position), color(color), texCoord(texCoord), normal(normal) { }

		static unsigned int Stride() { return sizeof(Vertex); }
	public:
		Vector3 position;
		Vector3 color;
		Vector3 normal;
		float2 texCoord;
	};
}