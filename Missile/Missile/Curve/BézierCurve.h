#pragma once

struct Vector2;

void GetPointBézier(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2);
void GetPointBézier(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2, const Vector2& p3);
void GetPointHermite(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& v0, const Vector2& v3);
//hermite

//class BézierCurve {
//public:
//    void GetPoint(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2);
//    void GetPoint(const Vector2& start, const Vector2& end, float t, Vector2& point, const Vector2& p2, const Vector2& p3);
//};