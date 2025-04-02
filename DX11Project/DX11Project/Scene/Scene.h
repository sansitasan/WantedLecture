#pragma once
#include <vector>
#include <memory>
#include "Type.h"

namespace SanDX {
	class Entity;

	class Scene {
	public:
		Scene();
		virtual ~Scene();

		virtual void BeginPlay();
		virtual void Update(float deltaTime);

		void AddEntity(std::shared_ptr<Entity> newEntity);

		std::shared_ptr<Entity> GetCamera();

		inline const std::shared_ptr<Entity>& GetEntity(int index) const { 
			if (index < 0 || index >= (int)entities.size()) return nullptr;
		
			return entities[index]; 
		}

		inline uint32 EntityCount() const { return (uint32)entities.size(); }

	protected:
		std::vector<std::shared_ptr<Entity>> entities;

		bool hasInitialize = false;

		std::shared_ptr<Entity> camera;
	};
}