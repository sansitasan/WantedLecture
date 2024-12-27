#pragma once
#include <iostream>

//�þ� ������ �ܼ��ϰ� �Ѵٸ� �Ÿ��� ������ ����
//������ forward ���Ϳ� �÷��̾�������� ������ ���հ��� ���� �þ߰��� 1/2���� ������ ���
//ȸ������ �ִٸ� world���� �׸�ŭ ȸ����Ų�ٸ� �װ� ������Ʈ�� forward, up, right ���Ͱ� �ȴ�
//�׷��� ȸ������ ����ص���

class Vector2
{
public:
	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 Add(const Vector2& other);

	Vector2 Multiply(const Vector2& other);

	float Dot(const Vector2& other);

	Vector2 operator+(const Vector2& other);

	Vector2 operator*(const Vector2& other);

	Vector2& operator+=(const Vector2& c);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
		os << "(" << vector.GetX() << ", " << vector.GetY() << ")\n";
		return os;
	}

	float operator[](int index);

	float GetX() const { return x; }
	float GetY() const { return y; }

private:
	float x;
	float y;
};

