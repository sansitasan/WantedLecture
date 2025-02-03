#pragma once
#include "Core.h"
#include <cmath>

//�þ� ������ �ܼ��ϰ� �Ѵٸ� �Ÿ��� ������ ����
//������ forward ���Ϳ� �÷��̾�������� ������ ���հ��� ���� �þ߰��� 1/2���� ������ ���
//ȸ������ �ִٸ� world���� �׸�ŭ ȸ����Ų�ٸ� �װ� ������Ʈ�� forward, up, right ���Ͱ� �ȴ�
//�׷��� ȸ������ ����ص���

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