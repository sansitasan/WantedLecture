#pragma once
#include "Core.h"

template<typename T>
struct ENGINE_API Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

	Vector3 Add(const Vector3& other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Multiply(const Vector3& other) {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	T Dot(const Vector3& other) {
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3 operator+(const Vector3& other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator*(const Vector3& other) {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	Vector3& operator+=(const Vector3& c) {
		(*this) = (*this) + c;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
		os << "(" << vector.GetX() << ", " << vector.GetY() << ", " << vector.GetZ() << ")\n";
		return os;
	}

	T operator[](int index) {
		if (index == 0) return x;
		else if (index == 1 || index == -1) return y;
		__debugbreak();
	}

	T GetX() const { return x; }
	T GetY() const { return y; }
	T GetZ() const { return z; }

private:
	T x;
	T y;
	T z;
};

