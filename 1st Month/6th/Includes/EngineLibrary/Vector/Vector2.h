#pragma once
#include "Core.h"
#include <cmath>

//시야 판정은 단순하게 한다면 거리와 방향을 본다
//몬스터의 forward 벡터와 플레이어까지와의 벡터의 사잇각을 보고 시야각의 1/2보다 작으면 통과
//회전값만 있다면 world축을 그만큼 회전시킨다면 그게 오브젝트의 forward, up, right 벡터가 된다
//그러니 회전값을 기록해두자

template<typename T>
struct ENGINE_API Vector2
{
public:
	static Vector2 Up = Vector2(0, 1);
	static Vector2 Down = Vector2(0, -1);
	static Vector2 Right = Vector2(1, 0);
	static Vector2 Left = Vector2(-1, 0);
	static Vector2 Zero = Vector2(0, 0);

public:
	Vector2() : x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}

	Vector2 Add(const Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Multiply(const Vector2& other) {
		return Vector2(x * other.x, y * other.y);
	}

	T Dot(const Vector2& other) {
		return x * other.x + y * other.y;
	}

	Vector2 Cross(const Vector2& other) {
		return Vector2(this->x * other.x + this->y * other.y, this->x * other.y - this->y * other.x);
	}

	T Magnitude() {
		return sqrt(x * x + y * y);
	}

	T Normalize() {
		T mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2 operator+(const Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) {
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(const Vector2& other) {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator/(const Vector2& other) {
		return Vector2(x / other.x, y / other.y);
	}

	Vector2& operator+=(const Vector2& other) {
		(*this) = (*this) + other;
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {
		(*this) = (*this) - other;
		return *this;
	}

	Vector2& operator*=(const Vector2& other) {
		(*this) = (*this) * other;
		return *this;
	}

	Vector2& operator/=(const Vector2& other) {
		(*this) = (*this) / other;
		return *this;
	}

	bool operator==(const Vector2& other) {
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(const Vector2& other) {
		return (x != other.x) || (y != other.y);
	}

	T operator[](int index) {
		if (index == 0) return x;
		else if (index == 1 || index == -1) return y;
		__debugbreak();
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
		os << "(" << vector.GetX() << ", " << vector.GetY() << ")\n";
		return os;
	}

	T GetX() const { return x; }
	T GetY() const { return y; }

private:
	T x;
	T y;
};