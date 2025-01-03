#pragma once

class Entity;

class ENGINE_API Scene
{
public:
	Scene();
	virtual ~Scene();

	void AddEntity(Entity* newEntity);

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	Entity** SceneEntityList;

	//���� ������ ������ ũ��
	int capacity;
	//������ ��
	int count;
};

