#include "TriangleMesh.h"
#include "Resource/MaterialLoader.h"
#include "Material/DefaultMaterial.h"

namespace SanDX {
	TriangleMesh::TriangleMesh()
	{
		std::vector<Vertex> vertices = {
			Vertex(Vector3(0, 0.5f, 0.5f), Vector3(1, 0, 0), Vector2(0.5f, 0.f), Vector3(0, 0, -1)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0, 1, 0), Vector2(1, 1), Vector3(0, 0, -1)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0, 0, 1), Vector2(0, 1), Vector3(0, 0, -1)),
		};

		std::vector<uint32> indices = { 0, 1, 2 };
		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
	}
}