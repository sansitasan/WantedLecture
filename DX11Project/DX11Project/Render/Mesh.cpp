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
		this->vertices.assign(vertices.begin(), vertices.end());
		stride = Vertex::Stride();
		this->indices.assign(indices.begin(), indices.end());

		//Buffer = 메모리 덩어리
		D3D11_BUFFER_DESC vertexBufferDesc = {};
		//x, y, z, 세 개 즉, 정점 세개
		vertexBufferDesc.ByteWidth = stride * (uint32)vertices.size();
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};

		vertexData.pSysMem = vertices.data();

		ID3D11Device& device = Engine::Get().Device();

		HRESULT result = device.CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
		RESULT(result, "Failed to create vertex buffer");

		D3D11_BUFFER_DESC indexBufferDesc = {};
		indexBufferDesc.ByteWidth = sizeof(uint32) * (uint32)indices.size();
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexData = {};

		indexData.pSysMem = indices.data();

		result = device.CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
		RESULT(result, "Failed to create index buffer");
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

	Mesh::Mesh()
	{

	}

	void Mesh::Draw()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		for (int32 i = 0; i < (int32)meshes.size(); ++i) {
			meshes[i]->Bind();
			materials[i]->Bind();
			//드로우 콜
			context.DrawIndexed(meshes[i]->IndexCount(), 0, 0);
		}
	}
}