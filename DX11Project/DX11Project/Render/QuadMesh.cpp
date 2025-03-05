#include "QuadMesh.h"
#include "Material/TextureMappingMaterial.h"
#include "Resource/MaterialLoader.h"

#include "Math/Matrix4x4.h"

//�ؽ�ó ������ ����
//������ �ٸ���(�ؽ�ó�� 2D, ������Ʈ�� 3D)
//�׷��� ����������� ��(����, ���)
//UV�� �迭�� �ε����� ���δ�. ?
//���ø��� ���� �������� ��

namespace SanDX {
	QuadMesh::QuadMesh()
	{
		std::vector<Vertex> vertices = {
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1, 1, 0), Vector2(1.f, 0.f), Vector3(0, 1, 0)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1, 0, 1), Vector2(1.f, 1.f), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0, 1, 1), Vector2(0.f, 1.f), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1, 1, 1), Vector2(0.f, 0.f), Vector3(0, 1, 0))
		};

		std::vector<uint32> indices = { 0, 2, 3, 0, 1, 2 };
		meshes.emplace_back(std::make_shared<MeshData>(vertices, indices));
		std::weak_ptr<TextureMappingMaterial> material;
		if (MaterialLoader::Get().Load<TextureMappingMaterial>(material, "head_face_M_BC.png")) {
			materials.emplace_back(material);
		}
	}
	void QuadMesh::Update(float deltaTime)
	{
		float angle = 60.f * deltaTime;
		Rotate(angle);
	}
	void QuadMesh::Rotate(float angle)
	{
		static std::vector<Vertex> result = {
			Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1, 1, 0), Vector2(1.f, 0.f), Vector3(0, 1, 0)),
			Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1, 0, 1), Vector2(1.f, 1.f), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0, 1, 1), Vector2(0.f, 1.f), Vector3(0, 1, 0)),
			Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(1, 1, 1), Vector2(0.f, 0.f), Vector3(0, 1, 0))
		};

		static float test = 1.001f;

		Matrix4x4 mat;
		Matrix4x4::Scale(test, mat);
		//Matrix4x4::RotationZ(angle, mat);
		for (__int8 i = 0; i < 4; ++i) {
			result[i].position = result[i].position * mat;
		}

		meshes[0]->UpdateVertexBuffer(result);
	}
}