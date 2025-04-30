#pragma once
#include "Entity.h"

namespace SanDX {
	class SphereEntity : public Entity {
	public:
		SphereEntity();
		~SphereEntity() = default;

		virtual void Update(float deltaTime) override;
	};
}