﻿#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector/Vector2.h"

class ENGINE_API Entity : public RTTI
{
	RTTI_DECLARATIONS(Entity, RTTI)

public:
	Entity();
	Entity(const Vector2& position);
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	inline virtual Vector2 GetPosition() const;
	virtual void SetPosition(const Vector2& newPosition);

	inline bool IsActive() const { return isActive && !isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	virtual void Destroy() { isExpired = true; }
	inline bool IsExpired() const { return isExpired; }

protected:
    bool isActive = true;
    //엔티티 제거 요청이 됐는지 여부를 나타내는 변수
    bool isExpired = false;
	//ID(해시), 이름, transform
	Vector2 position;
};