#pragma once

//Ctrl + K -> Ctrl + O하면 헤더 <-> cpp 이동
class IEntity {
public:
	//Entity();
	//virtual ~Entity();

	//void Move(int xAmount, int yAmount) = 0;
	virtual const char* GetName() = 0;//{ return "Entity"; }

protected:
	int x;
	int y;
};