#include "Vector2.h"
#include <Windows.h>
#include <cmath>
#include <cassert>

namespace SanDX {
    const Vector2 Vector2::Zero = Vector2(0, 0);
    const Vector2 Vector2::One = Vector2(1, 1);
    const Vector2 Vector2::Up = Vector2(1, 0);
    const Vector2 Vector2::Down = Vector2(-1, 0);
    const Vector2 Vector2::Left = Vector2(0, -1);
    const Vector2 Vector2::Right = Vector2(0, 1);
}