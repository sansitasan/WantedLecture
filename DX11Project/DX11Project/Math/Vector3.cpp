#pragma once
#include "Vector3.h"
//#include "Vector2.h"

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
}
