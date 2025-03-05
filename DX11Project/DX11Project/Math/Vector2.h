#pragma once
#include "../Type.h"
#include <cmath>
#include <intrin.h>
#include <string>
#include <cassert>
#include <iostream>

namespace SanDX {
	struct Vector2
	{
	public:
		const static Vector2 Up;
		const static Vector2 Down;
		const static Vector2 Left;
		const static Vector2 Right;
		const static Vector2 Zero;
		const static Vector2 One;

	public:
		Vector2() : value({}) {}
		Vector2(float x, float y) : value(MM128Union(x, y)) {}
		Vector2(int x, int y) : value(MM128Union((float)x, (float)y)) {}
		Vector2(__m128 value) : value(value) {}

		inline std::wstring ToString()
		{
			wchar_t buffer[256];
			swprintf_s(buffer, 256, L"(%f, %f)", value.fval[0], value.fval[1]);
			return buffer;
		}

		inline float Length()
		{
			__m128 mul = _mm_mul_ps(value.val, value.val);
			return sqrtf(mul.m128_f32[0] + mul.m128_f32[1]);
		}

		inline float LengthSquared()
		{
			__m128 mul = _mm_mul_ps(value.val, value.val);
			return mul.m128_f32[0] + mul.m128_f32[1];
		}

		inline friend Vector2 operator*(const Vector2& vector, const float other) {
			return Vector2(_mm_mul_ps(vector.value.val, _mm_set_ps1(other)));
		}

		inline friend Vector2 operator*(const float other, const Vector2& vector) {
			return Vector2(_mm_mul_ps(vector.value.val, _mm_set_ps1(other)));
		}

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
			return Vector2(_mm_div_ps(value.val, _mm_set_ps1(mag)));
		}

		inline void normalize() {
			float mag = Magnitude();

			value = _mm_div_ps(value.val, _mm_set_ps1(mag));
		}

		inline Vector2 operator+(const Vector2& other) const {
			return Vector2(_mm_add_ps(value.val, other.value.val));
		}

		inline Vector2 operator-(const Vector2& other) const {
			return Vector2(_mm_sub_ps(value.val, other.value.val));
		}

		inline Vector2 operator/(const float other) const {
			if (other == 0) __debugbreak();
			return Vector2(_mm_div_ps(value.val, _mm_set_ps1(other)));
		}

		inline Vector2 GetIntVector2() const {
			return Vector2((int)value.fval[0], (int)value.fval[1]);
		}

		Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
		{
			t = (t < 0 ? 0 : t) > 1 ? 1 : t;
			return (1.f - t) * from + t * to;
		}

		inline Vector2 Normalized()
		{
			float len = Length();
			assert(len != 0);

			return Vector2(_mm_div_ps(value.val, _mm_set_ps1(len)));
		}

		inline void normalized()
		{
			float len = Length();
			assert(len != 0);
			value = _mm_div_ps(value.val, _mm_set_ps1(len));
		}

		inline bool Equals(const Vector2& other)
		{
			return *this == other;
		}

		inline Vector2 operator-() const
		{
			return Vector2(-value.fval[0], -value.fval[1]);
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

		inline __m128 GetSIMDValue() const { return value.val; }
		inline const __m128& GetSIMDReference() const { return value.val; }

	private:
		union MM128Union {
			__m128 val;
			float fval[4];
			MM128Union(__m128 val) : val(val) {}
			MM128Union(float x, float y) : fval{ x, y, 0.f, 0.f } {}
		};

		MM128Union value;
	};
}