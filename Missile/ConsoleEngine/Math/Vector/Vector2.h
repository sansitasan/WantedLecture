#pragma once
#include "Core.h"
#include <cmath>
#include <intrin.h>
#include <cassert>


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
    Vector2() : value({}) {}
	Vector2(float x, float y) : value(MM128Union(x, y)) {}
    Vector2(int x, int y) : value(MM128Union((float)x, (float)y)) {}
    Vector2(__m128 value) : value(value) {}

	inline Vector2 Add(const Vector2& other) const {
		return Vector2(_mm_add_ps(value.val, other.value.val));
	}

	inline float Dot(const Vector2& other) const {
        __m128 mul = _mm_mul_ps(value.val, other.value.val);
		return mul.m128_f32[0] + mul.m128_f32[1];
	}

	inline float Magnitude() const {
        __m128 mul = _mm_mul_ps(value.val, value.val);
		return sqrt(mul.m128_f32[0] + mul.m128_f32[1]);
	}

    inline float SqrMagnitude() const {
        __m128 mul = _mm_mul_ps(value.val, value.val);
        return mul.m128_f32[0] + mul.m128_f32[1];
    }

	inline Vector2 Normalize() const {
		float mag = Magnitude();
        assert(mag != 0);
		return Vector2(_mm_div_ps(value.val, _mm_set_ps1(mag)));
	}

	inline void normalize() {
		float mag = Magnitude();
        assert(mag != 0);
        value.val = _mm_div_ps(value.val, _mm_set_ps1(mag));
		value.fval[0] /= mag;
		value.fval[1] /= mag;
	}

	inline Vector2 operator+(const Vector2& other) const {
		return Vector2(_mm_add_ps(value.val, other.value.val));
	}

	inline Vector2 operator-(const Vector2& other) const  {
		return Vector2(_mm_sub_ps(value.val, other.value.val));
	}

	inline ENGINE_API friend Vector2 operator*(const Vector2& vector, float other)  {
		return Vector2(_mm_mul_ps(vector.value.val, _mm_set_ps1(other)));
	}

    inline ENGINE_API friend Vector2 operator*(float other, const Vector2& vector) {
        return Vector2(_mm_mul_ps(vector.value.val, _mm_set_ps1(other)));
    }

	inline Vector2 operator/(float other) const {
        assert(other != 0);
		return Vector2(_mm_div_ps(value.val, _mm_set_ps1(other)));
	}

	inline Vector2 GetIntVector2() const {
		return Vector2((int)value.fval[0], (int)value.fval[1]);
	}

	inline Vector2& operator+=(const Vector2& other) {
		(*this) = (*this) + other;
		return *this;
	}

	inline Vector2& operator-=(const Vector2& other) {
		(*this) = (*this) - other;
		return *this;
	}

	inline Vector2& operator*=(float other) {
		(*this) = (*this) * other;
		return *this;
	}

	inline Vector2& operator/=(float other) {
		(*this) = (*this) / other;
		return *this;
	}

	inline bool IntCompare(const Vector2& other) const {
		return (int)value.fval[1] == (int)other.value.fval[1] && (int)value.fval[0] == (int)other.value.fval[0];
	}

	inline bool operator==(const Vector2& other) const {
		return (value.fval[0] == other.value.fval[0]) && (value.fval[1] == other.value.fval[1]);
	}

	inline bool operator!=(const Vector2& other) const {
		return (value.fval[0] != other.value.fval[0]) || (value.fval[1] != other.value.fval[1]);
	}

	inline float operator[](int index) const {
		if (index == 0) return value.fval[0];
		else if (index == 1 || index == -1) return value.fval[1];
		__debugbreak();
		return value.fval[0];
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
		os << "(" << vector.GetX() << ", " << vector.GetY() << ")\n";
		return os;
	}

	inline float GetX() const { return value.fval[0]; }
	inline float GetY() const { return value.fval[1]; }

	inline void SetX(float value) { this->value.fval[0] = value; }
	inline void SetY(float value) { this->value.fval[1] = value; }

private:
    union ENGINE_API MM128Union {
        __m128 val;
        float fval[2];
        MM128Union(__m128 val) : val(val) {}
        MM128Union(float x, float y) : fval{x, y} {}
    };

    MM128Union value;
};