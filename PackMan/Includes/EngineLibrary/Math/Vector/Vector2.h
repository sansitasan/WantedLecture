#pragma once
#include "Core.h"
#include <cmath>

//�þ� ������ �ܼ��ϰ� �Ѵٸ� �Ÿ��� ������ ����
//������ forward ���Ϳ� �÷��̾�������� ������ ���հ��� ���� �þ߰��� 1/2���� ������ ���
//ȸ������ �ִٸ� world���� �׸�ŭ ȸ����Ų�ٸ� �װ� ������Ʈ�� forward, up, right ���Ͱ� �ȴ�
//�׷��� ȸ������ ����ص���

struct ENGINE_API Vector2
{
public:
	const static Vector2 Up;
	const static Vector2 Down;
	const static Vector2 Left;
	const static Vector2 Right;
	const static Vector2 Zero;
public:
	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(int x, int y) : x((float)x), y((float)y) {}

	inline Vector2 Add(const Vector2& other);

	inline Vector2 Multiply(const Vector2& other);

	inline float Dot(const Vector2& other);

	inline Vector2 Cross(const Vector2& other);

	inline float Magnitude();

	inline Vector2 Normalize();

	inline void normalize();

	inline Vector2 operator+(const Vector2& other);

	inline Vector2 operator-(const Vector2& other);

	inline Vector2 operator*(const float other);

	inline Vector2 operator*(const Vector2& other);

	inline Vector2 operator/(const float other);

	inline Vector2 operator/(const Vector2& other);

	inline Vector2& operator+=(const Vector2& other);

	inline Vector2& operator-=(const Vector2& other);

	inline Vector2& operator*=(const Vector2& other);

	inline Vector2& operator/=(const Vector2& other);

	inline bool IntCompare(const Vector2& other);

	inline bool operator==(const Vector2& other);

	inline bool operator!=(const Vector2& other);

	inline float operator[](int index);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

	inline float GetX() const { return x; }
	inline float GetY() const { return y; }

private:
	float x;
	float y;
};