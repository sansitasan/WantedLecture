#pragma once

namespace SanDX {
	class Vector4 {
	public:
		float x;
		float y;
		float z;
		float w;

		inline Vector4()
			: x(0), y(0), z(0), w(0) {
		}

		inline Vector4(float value)
			: x(value), y(value), z(value), w(1) {
		}

		inline Vector4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {
		}
	};
}