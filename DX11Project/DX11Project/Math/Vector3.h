#pragma once
#include "../Type.h"
#include <string>

namespace SanDX {
	class Vector3 {
	public:
		float x = .0f;
		float y = .0f;
		float z = .0f;

		inline Vector3()
			: x(0), y(0), z(0) {}

		inline Vector3(float value)
			: x(value), y(value), z(value) {}
		
		inline Vector3(float x, float y, float z)
			: x(x), y(y), z(z) { }

		//inline Vector3(const class Vector2& other);

		inline static uint32 Stride() { return sizeof(Vector3); }

		inline Vector3& operator+=(const Vector3& other);
		inline Vector3& operator-=(const Vector3& other);

		inline Vector3& operator*=(float scale);
		inline Vector3& operator/=(float scale);

		inline friend Vector3 operator+(const Vector3& left, const Vector3& right);
		inline friend Vector3 operator-(const Vector3& left, const Vector3& right);

		inline friend Vector3 operator*(const Vector3& vector, float scale){
			return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
		}

		inline friend Vector3 operator*(float scale, const Vector3& vector) {
			return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
		}

		inline friend Vector3 operator/(const Vector3& vector, float scale);

		inline Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		inline bool operator==(const Vector3& other);
		inline bool operator!=(const Vector3& other);

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Forward;
		static const Vector3 Back;

		std::wstring ToString();

		inline float Length();
		inline float LengthSquared();
		inline friend float Dot(const Vector3& left, const Vector3& right);
		inline friend Vector3 Cross(const Vector3& left, const Vector3& right);
		inline friend Vector3 Lerp(const Vector3& from, const Vector3& to, float t);
		inline Vector3 Normalized();
		inline void normalized();
		inline bool Equals(const Vector3& other);
	};
}