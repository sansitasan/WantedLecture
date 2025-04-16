#pragma once

#include "Entity.h"

namespace SanDX {
	class CameraEntity : public Entity {
	public:
		CameraEntity();
		virtual void Update(float deltaTime) override;
		
	private:
		void Move(float deltaTime);
		inline void Rotate();
	};
}