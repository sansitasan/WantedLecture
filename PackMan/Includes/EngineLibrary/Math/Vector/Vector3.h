#pragma once
#include "Core.h"

struct ENGINE_API Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 Add(const Vector3& other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 Multiply(const Vector3& other) {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	float Dot(const Vector3& other) {
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

	float operator[](int index) {
		if (index == 0) return x;
		else if (index == 1 || index == -1) return y;
		__debugbreak();
	}

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetZ() const { return z; }

private:
	float x;
	float y;
	float z;
};

