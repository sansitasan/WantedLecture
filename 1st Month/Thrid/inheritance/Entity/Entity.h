#pragma once

//Ctrl + K -> Ctrl + O�ϸ� ��� <-> cpp �̵�
class Entity {
public:
	Entity();
	Entity(int, int);
	~Entity();

	void Move(int xAmount, int yAmount);
protected:
	int x;
	int y;
};