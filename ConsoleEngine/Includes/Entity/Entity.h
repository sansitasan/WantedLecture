#pragma once
#include "Core.h"
#include "RTTI.h"

class ENGINE_API Entity : public RTTI
{
	RTTI_DECLARATIONS(Entity, RTTI)

public:
	Entity();
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();
protected:
	//ID(�ؽ�), �̸�, transform

	bool isActive = true;
	//��ƼƼ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpried = false;
};