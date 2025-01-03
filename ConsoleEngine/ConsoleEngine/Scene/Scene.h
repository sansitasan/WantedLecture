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

	//저장 가능한 공간의 크기
	int capacity;
	//액터의 수
	int count;
};

