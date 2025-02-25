#pragma once
#include "../Type.h"
#include <string>

namespace SanDX {
	class Vector2 {
	public:
		float x = .0f;
		float y = .0f;

		Vector2()
			: x(0), y(0) {}

		Vector2(float value)
			: x(value), y(value) {}

		Vector2(float x, float y)
			: x(x), y(y) {}

		inline static uint32 Stride() { return sizeof(Vector2); }

		inline Vector2& operator+=(const Vector2& other);
		inline Vector2& operator-=(const Vector2& other);
		inline Vector2& operator*=( float scale);
		inline Vector2& operator/=( float scale);

		inline friend Vector2 operator+(const Vector2& left, const Vector2& right);
		inline friend Vector2 operator-(const Vector2& left, const Vector2& right);
		inline friend Vector2 operator*(const Vector2& vector,  float scale);
		inline friend Vector2 operator*(float scale, const Vector2& vector);
		inline friend Vector2 operator/(const Vector2& vector,  float scale);

		inline Vector2 operator-() const;

		inline bool operator==(const Vector2& other);
		inline bool operator!=(const Vector2& other);

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Left;
		static const Vector2 Right;

		std::wstring ToString();

		inline float Length();
		inline float LengthSquared();
		inline friend float Dot(const Vector2& left, const Vector2& right)
		{
			return left.x * right.x + left.y * right.y;
		}
		inline friend Vector2 Lerp(const Vector2& from, const Vector2& to, float t);
		inline Vector2 Normalized();
		inline void normalized();
		inline bool Equals(const Vector2& other);
	};
}