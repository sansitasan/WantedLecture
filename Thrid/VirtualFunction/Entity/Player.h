#pragma once
#include "Entity.h"
#include "IMovable.h"

class Player : public IEntity, public IMovable
{
public:
	Player(const char* name);
	~Player();

	//override�� ���̴� ������ �������� �Ǽ�����
	//v-table�� ����
	virtual const char* GetName() override { return name; }
	virtual void Move(int xAmount, int yAmount) override {}

private:
	char* name;
};

