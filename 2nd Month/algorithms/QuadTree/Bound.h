#pragma once

class Bound {
public:
	Bound(int x = 0,int y = 0, int width = 1, int height = 1)
		: x(x), y(y), width(width), height(height) { }

	inline int X() const { return x; }
	inline int Y() const { return y; }
	inline int Width() const { return width; }
	inline int Height() const { return height; }

	inline int MaxX() const { return x + width; }
	inline int MaxY() const { return y + height; }

	inline bool Intersects(const Bound& other) const {
		if (other.x > MaxX()) return false;
		if (other.y > MaxY()) return false;
		if (other.MaxX() < x) return false;
		if (other.MaxY() < y) return false;
		return true;
	}

private:
	int x = 0;
	int y = 0;
	int width = 1;
	int height = 1;
};