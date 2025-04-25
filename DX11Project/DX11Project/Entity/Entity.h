#pragma once
#include <string>
#include "Math/Transform.h"

namespace SanDX {
	class Entity {
	public:
		Entity();
		virtual ~Entity();

		virtual void BeginPlay();
		virtual void Update(float deltaTime);
		virtual void Draw();

		FORCEINLINE void Destroy() { hasDestroyed = false; }

		FORCEINLINE const bool IsActive() const { return isActive && !hasDestroyed; }
		FORCEINLINE const bool HasInitialized() const { return hasInitialized && !hasDestroyed; }

		FORCEINLINE void SetActive(bool newActive) { isActive = newActive; }

	public:
		Transform transform;

	protected:
		//�Ϲ������δ� hash�� ��ȯ�ؼ� ����Ѵ�.
		std::wstring name = TEXT("Entity");

		bool hasInitialized = false;
		bool isActive = false;
		bool hasDestroyed = false;
	};
}