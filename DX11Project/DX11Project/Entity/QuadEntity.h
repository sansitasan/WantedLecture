#pragma once
#include "Entity.h"

namespace SanDX {
	class QuadEntity : public Entity {
	public:
		QuadEntity();
		~QuadEntity() = default;

		virtual void Update(float deltaTime) override;
	};
}