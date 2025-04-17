#pragma once
#include "../Type.h"
#include <string>
#include <cassert>
#include <Windows.h>
#include <cmath>

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

		inline Vector3& operator+=(const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		inline Vector3& operator-=(const Vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		inline Vector3& operator*=(float scale) {
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}

		inline Vector3& operator/=(float scale) {
			assert(scale != 0);
			x /= scale;
			y /= scale;
			z /= scale;
			return *this;
		}

		inline friend Vector3 operator+(const Vector3& left, const Vector3& right) {
			return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
		}

		inline friend Vector3 operator-(const Vector3& left, const Vector3& right) {
			return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
		}

		inline friend Vector3 operator*(const Vector3& vector, float scale){
			return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
		}

		inline friend Vector3 operator*(float scale, const Vector3& vector) {
			return Vector3(vector.x * scale, vector.y * scale, vector.z * scale);
		}

		inline friend Vector3 operator/(const Vector3& vector, float scale) {
			assert(scale != 0);

			return Vector3(vector.x / scale, vector.y / scale, vector.z / scale);
		}

		inline Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}

		inline bool operator==(const Vector3& other) {
			return x == other.x && y == other.y && z == other.z;
		}

		inline bool operator!=(const Vector3& other) {
			return x != other.x || y != other.y || z != other.z;
		}

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Forward;
		static const Vector3 Back;

		std::wstring ToString() {
			wchar_t buffer[256];
			swprintf_s(buffer, 256, TEXT("(%f, %f, %f)"), x, y, z);
			return buffer;
		}

		inline float Length() {
			return sqrtf(x * x + y * y + z * z);
		}

		inline float LengthSquared() {
			return x * x + y * y + z * z;
		}

		inline friend float Dot(const Vector3& left, const Vector3& right) {
			return left.x * right.x + left.y * right.y + left.z * right.z;
		}

		inline friend Vector3 Cross(const Vector3& left, const Vector3& right) {
			//기저 벡터, left, right로 외적을 구한다
			//기저 벡터가 각각 i, j, k일 때,
			// |  i  j  k | i * (ly * rz - lz * ry)
			// | lx ly lz | j * (lz * rx - lx * rz)
			// | rx ry rz | k * (lx * ry - ly * rx)

			return Vector3
			(
				left.y * right.z - left.z * right.y,
				left.z * right.x - left.x * right.z,
				left.x * right.y - left.y * right.x
			);
		}

		inline friend Vector3 Lerp(const Vector3& from, const Vector3& to, float t) {
			t = (t < 0 ? 0 : t) > 1 ? 1 : t;
			return (1.f - t) * from + t * to;
		}

		inline Vector3 Normalized() {
			float len = Length();
			assert(len != 0);
			return Vector3(x / len, y / len, z / len);
		}

		inline void normalized() {
			float len = Length();
			assert(len != 0);
			x /= len;
			y /= len;
			z /= len;
		}

		inline bool Equals(const Vector3& other) {
			return x == other.x && y == other.y && z == other.z;
		}
	};
}