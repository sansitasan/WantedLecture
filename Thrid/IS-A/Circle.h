#pragma once
#include <iostream>

class Point {
public:
	Point(double x, double y) : x(x), y(y) {}

protected:
	double x;
	double y;
};

class Circle : public Point
{
public:
	Circle(double x, double y, double r) : Point(x, y), r(r) { }

	void ShowData() {
		std::cout << "중심 좌표: (" << x << ", " << y << ")\n";
		std::cout << "반지름: " << r << "\n";
		std::cout << "원의 넓이: " << r * r * 3.1415f << "\n";
	}

	~Circle() {
	}

private:
	double r;
};