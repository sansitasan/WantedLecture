#include "QuadMesh.h"
#include "Material/TextureMappingMaterial.h"

//텍스처 매핑의 이유
//차원이 다르다(텍스처는 2D, 오브젝트는 3D)
//그래서 대응시켜줘야 함(대응, 사상)
//UV는 배열의 인덱스로 쓰인다. ?
//샘플링은 값을 가져오는 것

namespace SanDX {
	QuadMesh::QuadMesh()
	{
		std::vector<Vertex> vertices = {
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1, 1, 0), Vector2(1, 0), Vector3(0, 1, 0)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1, 0, 1), Vector2(1, 1), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0, 1, 1), Vector2(0, 1), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1, 1, 1), Vector2(0, 0), Vector3(0, 1, 0))
		};

		std::vector<uint32> indices = { 0, 2, 3, 0, 1, 2 };
		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		materials.emplace_back(std::make_shared<TextureMappingMaterial>("head_face_M_BC.png"));
	}
}