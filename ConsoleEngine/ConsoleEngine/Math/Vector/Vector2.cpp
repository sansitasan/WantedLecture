#include "PreCompiledHeader.h"
#include "Vector2.h"

const Vector2 Up = Vector2(0, 1);
const Vector2 Down = Vector2(0, -1);
const Vector2 Right = Vector2(1, 0);
const Vector2 Left = Vector2(-1, 0);
const Vector2 Zero = Vector2(0, 0);

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

Vector2 Vector2::Cross(const Vector2& other)
{
	return Vector2(this->x * other.x + this->y * other.y, this->x * other.y - this->y * other.x);
}

float Vector2::Magnitude()
{
	return sqrt(x * x + y * y);
}

Vector2 Vector2::Normalize()
{
	float mag = Magnitude();
	return Vector2(x / mag, y / mag);
}

void Vector2::normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(const Vector2& other)
{
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator/(const Vector2& other)
{
	return Vector2(x / other.x, y / other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	(*this) = (*this) + other;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	(*this) = (*this) - other;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	(*this) = (*this) * other;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	(*this) = (*this) / other;
	return *this;
}

bool Vector2::operator==(const Vector2& other)
{
	return (x == other.x) && (y == other.y);
}

bool Vector2::operator!=(const Vector2& other)
{
	return (x != other.x) || (y != other.y);
}

float Vector2::operator[](int index)
{
	if (index == 0) return x;
	else if (index == 1 || index == -1) return y;
	__debugbreak();
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
	os << "(" << vector.GetX() << ", " << vector.GetY() << ")\n";
	return os;
}
