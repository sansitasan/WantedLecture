#pragma once
#include <vector>
#include <d3d11.h>
#include "Vertex.h"
#include "Type.h"
#include <memory>
#include "Material/Material.h"
#include "Core.h"

namespace SanDX {
	struct MeshData {
		MeshData();
		MeshData(const std::vector<Vertex>& vertices, const std::vector<uint32> indices);
		~MeshData();

		void Bind();
		inline uint32 IndexCount() const { return (uint32)indices.size(); }

		void UpdateVertexBuffer(const std::vector<Vertex>& vertices);
		//정점, 인덱스 등을 가지고 있을 데이터
		std::vector<Vertex> vertices;
		ID3D11Buffer* vertexBuffer = nullptr;

		std::vector<uint32> indices;
		ID3D11Buffer* indexBuffer = nullptr;

		uint32 stride = 0;
	};

	class Mesh {
	public:
		Mesh();
		virtual ~Mesh() = default;

		virtual void Draw();
	protected:
		std::vector<std::shared_ptr<MeshData>> meshes;
		std::vector<std::weak_ptr<class Material>> materials;
	};
}