#pragma once

class ENGINE_API Entity
{
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