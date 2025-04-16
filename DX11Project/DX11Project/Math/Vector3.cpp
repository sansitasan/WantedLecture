#pragma once
#include "Vector3.h"
//#include "Vector2.h"
#include <Windows.h>
#include <cmath>

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

	inline float Vector3::LengthSquared()
	{
		return x * x + y * y + z * z;
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

	inline Vector3 Lerp(const Vector3& from, const Vector3& to, float t)
	{
		t = (t < 0 ? 0 : t) > 1 ? 1 : t;
		return (1.f - t) * from + t * to;
	}
}
