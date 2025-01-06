#pragma once

class ENGINE_API Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();
protected:
	//ID(해시), 이름, transform

	bool isActive = true;
	//엔티티 제거 요청이 됐는지 여부를 나타내는 변수
	bool isExpried = false;
};