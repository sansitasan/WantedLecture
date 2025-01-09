#pragma once
#include "Core.h"
#include "RTTI.h"
#include "Math/Vector/Vector2.h"

class ENGINE_API Entity : public RTTI
{
	RTTI_DECLARATIONS(Entity, RTTI)

public:
	Entity();
	virtual ~Entity();

	virtual void Update(float deltaTime);
	virtual void Draw();

	inline Vector2 GetPosition() const;
	virtual void SetPosition(const Vector2& newPosition);

	bool IsActive() const { return isActive; }
	void SetActive(bool active) { isActive = active; }
	void Destroy() { isExpired = true; }
	bool IsExpired() const { return isExpired; }

protected:
	//ID(해시), 이름, transform
	Vector2 position;

	bool isActive = true;
	//엔티티 제거 요청이 됐는지 여부를 나타내는 변수
	bool isExpired = false;
};