#pragma once
#include "../Vector/Vector2.h"

constexpr float PI = 3.1415927f;

struct ENGINE_API Matrix2x2 {
public:
    Matrix2x2(const Vector2& x, const Vector2& y)
        : x(x), y(y) { }
    Matrix2x2(float x1, float x2, float y1, float y2)
        : x(x1, x2), y(y1, y2) { }

    inline const Vector2& GetX() const { return x; }
    inline const Vector2& GetY() const { return y; }

    const static Matrix2x2 Rad30;
    const static Matrix2x2 Rad45;
    const static Matrix2x2 Rad60;
    const static Matrix2x2 Rad90;
    const static Matrix2x2 Rad180;

private:
    Vector2 x;
    Vector2 y;
};

inline ENGINE_API Vector2 Rotate(const Matrix2x2& mat, const Vector2& position) {
    return Vector2(position.Dot(mat.GetX()), position.Dot(mat.GetY()));
}