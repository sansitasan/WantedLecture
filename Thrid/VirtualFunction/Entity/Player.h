#pragma once
#include "Entity.h"
#include "IMovable.h"

class Player : public IEntity, public IMovable
{
public:
	Player(const char* name);
	~Player();

	//override를 붙이는 이유는 가독성과 실수방지
	//v-table은 정적
	virtual const char* GetName() override { return name; }
	virtual void Move(int xAmount, int yAmount) override {}

private:
	char* name;
};

