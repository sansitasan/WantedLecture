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
	//ID(�ؽ�), �̸�, transform
	Vector2 position;

	bool isActive = true;
	//��ƼƼ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����
	bool isExpired = false;
};