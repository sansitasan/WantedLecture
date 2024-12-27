#include "Vector2.h"

Vector2 Vector2::Add(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::Multiply(const Vector2& other)
{
	return Vector2(x * other.x, y * other.y);
}

float Vector2::Dot(const Vector2& other)
{
	return x * other.x + y * other.y;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator*(const Vector2& other)
{
	return Vector2(x * other.x, y * other.y);
}

Vector2& Vector2::operator+=(const Vector2& c) {
	(*this) = (*this) + c;
	return *this;
}

float Vector2::operator[](int index)
{
	//TODO: 2 이상은 쳐내기
	if (index)
		return y;
	return x;
}
