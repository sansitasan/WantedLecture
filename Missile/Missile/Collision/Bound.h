#pragma once
#include <Math/Vector/Vector2.h>

class Bound {
public:
    Bound(const Vector2& leftUp, const Vector2& rightBottom)
        : leftUp(leftUp), rightBottom(rightBottom) { }

    inline const Vector2& LeftUp() const { return leftUp; }
    inline const Vector2& RightBottom() const { return rightBottom; }

    inline bool Intersects(const Vector2& other) const {
        if (other.GetX() > rightBottom.GetX()) return false;
        if (other.GetY() > rightBottom.GetY()) return false;
        if (other.GetX() < leftUp.GetX()) return false;
        if (other.GetY() < leftUp.GetY()) return false;
        return true;
    }

private:
    Vector2 leftUp;
    Vector2 rightBottom;
};