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
		//일반적으로는 hash로 변환해서 사용한다.
		std::wstring name = TEXT("Entity");

		bool hasInitialized = false;
		bool isActive = false;
		bool hasDestroyed = false;
	};
}