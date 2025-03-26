#pragma once
#include "Vector3.h"
//#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <cassert>

namespace SanDX {
	const Vector3 Vector3::Zero = Vector3();
	const Vector3 Vector3::One = Vector3(1);
	const Vector3 Vector3::Up = Vector3(0, 1, 0);
	const Vector3 Vector3::Down = Vector3(0, -1, 0);
	const Vector3 Vector3::Left = Vector3(-1, 0, 0);
	const Vector3 Vector3::Right = Vector3(1, 0, 0);
	const Vector3 Vector3::Forward = Vector3(0, 0, 1);
	const Vector3 Vector3::Back = Vector3(0, 0, -1);

	//inline Vector3::Vector3(const Vector2& other)
	//	: x(other.x), y(other.y), z(0) {}

	inline Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	inline Vector3& Vector3::operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
		return *this;
	}

	inline Vector3& Vector3::operator/=(float scale)
	{
		assert(scale != 0);
		x /= scale;
		y /= scale;
		z /= scale;
		return *this;
	}

	inline Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline bool Vector3::operator==(const Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	inline bool Vector3::operator!=(const Vector3& other)
	{
		return x != other.x || y != other.y || z != other.z;
	}

	inline std::wstring Vector3::ToString()
	{
		wchar_t buffer[256];
		swprintf_s(buffer, 256, TEXT("(%f, %f, %f)"), x, y, z);
		return buffer;
	}

	inline float Vector3::Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	inline float Vector3::LengthSquared()
	{
		return x * x + y * y + z * z;
	}

	inline Vector3 Vector3::Normalized()
	{
		float len = Length();
		assert(len != 0);
		return Vector3(x / len, y / len, z / len);
	}

	inline void Vector3::normalized()
	{
		float len = Length();
		assert(len != 0);
		x /= len;
		y /= len;
		z /= len;
	}

	inline bool Vector3::Equals(const Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	inline Vector3 operator+(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	inline Vector3 operator-(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	inline Vector3 operator/(const Vector3& vector, float scale)
	{
		assert(scale != 0);

		return Vector3(vector.x / scale, vector.y / scale, vector.z / scale);
	}

	inline float Dot(const Vector3& left, const Vector3& right)
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	inline Vector3 Cross(const Vector3& left, const Vector3& right)
	{
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

	inline Vector3 Lerp(const Vector3& from, const Vector3& to, float t)
	{
		t = (t < 0 ? 0 : t) > 1 ? 1 : t;
		return (1.f - t) * from + t * to;
	}
}
