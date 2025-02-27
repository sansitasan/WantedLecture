#include "BézierCurve.h"
#include <Math/Vector/Vector2.h>

void GetPointBézier(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2)
{
    point = (start * (1.f - t) + p2 * t) * (1.f - t) + (p2 * (1.f - t) + end * t) * t;
}

void GetPointBézier(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2, const Vector2& p3)
{
    point = start * ((1.f - t) * (1.f - t) * (1.f - t)) + p2 * (3 * t * (1.f - t) * (1.f - t)) + p3 * (3 * t * t * (1.f - t)) + end * t * t * t;
}

void GetPointHermite(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& v0, const Vector2& v3)
{
    point = start * (2 * t * t * t - 3 * t * t + 1) + v0 * (t * t * t - 2 * t * t + t) + end * (-2 * t * t * t + 3 * t * t) + v3 * (t * t * t - t * t);
}
