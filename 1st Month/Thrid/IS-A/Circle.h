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
		std::cout << "�߽� ��ǥ: (" << x << ", " << y << ")\n";
		std::cout << "������: " << r << "\n";
		std::cout << "���� ����: " << r * r * 3.1415f << "\n";
	}

	~Circle() {
	}

private:
	double r;
};