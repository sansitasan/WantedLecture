#include "QuadMesh.h"
#include "Material/TextureMappingMaterial.h"

//�ؽ�ó ������ ����
//������ �ٸ���(�ؽ�ó�� 2D, ������Ʈ�� 3D)
//�׷��� ����������� ��(����, ���)
//UV�� �迭�� �ε����� ���δ�. ?
//���ø��� ���� �������� ��

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