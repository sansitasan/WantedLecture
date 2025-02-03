#pragma once
#include "Core.h"
#include <cmath>

//시야 판정은 단순하게 한다면 거리와 방향을 본다
//몬스터의 forward 벡터와 플레이어까지와의 벡터의 사잇각을 보고 시야각의 1/2보다 작으면 통과
//회전값만 있다면 world축을 그만큼 회전시킨다면 그게 오브젝트의 forward, up, right 벡터가 된다
//그러니 회전값을 기록해두자

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

	Vector2 Add(const Vector2& other);

	Vector2 Multiply(const Vector2& other);

	float Dot(const Vector2& other);

	Vector2 Cross(const Vector2& other);

	float Magnitude();

	Vector2 Normalize();

	void normalize();

	Vector2 operator+(const Vector2& other);

	Vector2 operator-(const Vector2& other);

	Vector2 operator*(const Vector2& other);

	Vector2 operator/(const Vector2& other);

	Vector2& operator+=(const Vector2& other);

	Vector2& operator-=(const Vector2& other);

	Vector2& operator*=(const Vector2& other);

	Vector2& operator/=(const Vector2& other);

	bool operator==(const Vector2& other);

	bool operator!=(const Vector2& other);

	float operator[](int index);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

	float GetX() const { return x; }
	float GetY() const { return y; }

private:
	float x;
	float y;
};