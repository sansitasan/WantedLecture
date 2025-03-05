#pragma once
#include "Mesh.h"

namespace SanDX {
	class QuadMesh : public Mesh {
	public:
		QuadMesh();

		void Update(float deltaTime);

		void Rotate(float angle);
	};
}