#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <cassert>

namespace SanDX {
    const Vector2 Vector2::Zero = Vector2(0);
    const Vector2 Vector2::One = Vector2(1);
    const Vector2 Vector2::Up = Vector2(1, 0);
    const Vector2 Vector2::Down = Vector2(-1, 0);
    const Vector2 Vector2::Left = Vector2(0, -1);
    const Vector2 Vector2::Right = Vector2(0, 1);

    inline std::wstring Vector2::ToString()
    {
        wchar_t buffer[256];
        swprintf_s(buffer, 256, TEXT("(%f, %f)"), x, y);
        return buffer;
    }

    inline float Vector2::Length()
    {
        return sqrtf(x * x + y * y);
    }

    inline float Vector2::LengthSquared()
    {
        return x * x + y * y;
    }

    Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
    {
        t = (t < 0 ? 0 : t) > 1 ? 1 : t;
        return (1.f - t) * from + t * to;
    }

    inline Vector2 Vector2::Normalized()
    {
        float len = Length();
        assert(len != 0);
        return Vector2(x / len, y / len);
    }

    inline void Vector2::normalized()
    {
        float len = Length();
        assert(len != 0);
        x /= len;
        y /= len;
    }

    inline bool Vector2::Equals(const Vector2& other)
    {
        return *this == other; 
    }

    inline Vector2& Vector2::operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline Vector2& Vector2::operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Vector2& Vector2::operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    inline Vector2& Vector2::operator/=(float scale)
    {
        assert(scale != 0.0f);

        x /= scale;
        y /= scale;
        return *this;
    }

    inline Vector2 operator+(const Vector2& left, const Vector2& right)
    {
        return Vector2(left.x + right.x, left.y + right.y);
    }

    inline Vector2 operator-(const Vector2& left, const Vector2& right)
    {
        return Vector2(left.x - right.x, left.y - right.y);
    }

    inline Vector2 operator*(const Vector2& vector, float scale)
    {
        return Vector2(vector.x * scale, vector.y * scale);
    }

    inline Vector2 operator*(float scale, const Vector2& vector)
    {
        return Vector2(vector.x * scale, vector.y * scale);;
    }

    inline Vector2 operator/(const Vector2& vector, float scale)
    {
        assert(scale != 0);
        return Vector2(vector.x / scale, vector.y / scale);
    }

    inline Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    inline bool Vector2::operator==(const Vector2& other)
    {
        return x == other.x && y == other.y;
    }

    inline bool Vector2::operator!=(const Vector2& other)
    {
        return x != other.x || y != other.y;
    }
}