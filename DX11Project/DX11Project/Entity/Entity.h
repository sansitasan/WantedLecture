#pragma once
#include <string>
#include "Math/Transform.h"
#include <memory>
#include <vector>

namespace SanDX {
	class Entity {
		friend class Renderer;
		friend class Scene;

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

		void AddComponent(std::shared_ptr<class Component> newComponent);

		template<typename T>
		bool TryGetComponent() {
			return true;
		}

	public:
		Transform transform;

	protected:
		//일반적으로는 hash로 변환해서 사용한다.
		std::wstring name = TEXT("Entity");

		bool hasInitialized = false;
		bool isActive = true;
		bool hasDestroyed = false;

		std::vector<std::shared_ptr<class Component>> components;
	};
}