#include "Mesh.h"
#include "Engine.h"
#include "Material/Material.h"

namespace SanDX {
	MeshData::MeshData()
	{
	}

	MeshData::MeshData(const std::vector<Vertex>& vertices, const std::vector<uint32> indices)
		: vertices(vertices), indices(indices)
	{
		stride = Vertex::Stride();
		UpdateVertexBuffer(vertices);

		ID3D11Device& device = Engine::Get().Device();

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};

		indexData.pSysMem = indices.data();

		HRESULT result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
		RESULT(result, TEXT("Failed to create index buffer"));
	}

	MeshData::~MeshData()
	{
		if (vertexBuffer) vertexBuffer->Release();
		vertexBuffer = nullptr;
		if (indexBuffer) indexBuffer->Release();
		indexBuffer = nullptr;
	}

	void MeshData::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();
		static uint32 offset = 0;
		context.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		context.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void MeshData::UpdateVertexBuffer(const std::vector<Vertex>& vertices)
	{
		this->vertices.assign(vertices.begin(), vertices.end());

		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}

		//Buffer = 메모리 덩어리
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		//x, y, z, 세 개 즉, 정점 세개
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};

		vertexData.pSysMem = this->vertices.data();

		ID3D11Device& device = Engine::Get().Device();

		HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
		RESULT(result, TEXT("Failed to create vertex buffer"));
	}

	Mesh::Mesh()
	{

	}

	void Mesh::Draw()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		for (int32 i = 0; i < (int32)meshes.size(); ++i) {
			std::shared_ptr<Material> shader = materials[i].lock();
			if (!shader) {
				continue;
			}
			meshes[i]->Bind();

			shader->Bind();
			//드로우 콜
			context.DrawIndexed(meshes[i]->IndexCount(), 0, 0);
		}
	}
}