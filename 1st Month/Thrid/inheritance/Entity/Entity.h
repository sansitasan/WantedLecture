#pragma once

//Ctrl + K -> Ctrl + O하면 헤더 <-> cpp 이동
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