#pragma once
#include <iostream>

class Point {
public:
	Point(double x, double y) : x(x), y(y) {}

	double GetX() {
		return x;
	}

	double GetY() {
		return y;
	}

private:
	double x;
	double y;
};

class Circle
{
public:
	Circle(double x, double y, double r)  : r(r){
		point = new Point(x, y);
	}

	void ShowData() {
		std::cout << "�߽� ��ǥ: (" << point->GetX() << ", " << point->GetY() << ")\n";
		std::cout << "������: " << r << "\n";
		std::cout << "���� ����: " << r * r * 3.1415f << "\n";
	}

	~Circle() {
		if (point) {
			delete point;
		}
	}

private:
	Point* point;
	double r;
};

