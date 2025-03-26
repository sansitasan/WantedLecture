#include "Transform.h"
#include "Engine.h"
#include "Core.h"

namespace SanDX {
	Transform::Transform()
	{
		Matrix4x4 s, r, t;
		Matrix4x4::Scale(scale, s); 
		Matrix4x4::Rotation(rotation, r); 
		Matrix4x4::Translation(position, t);
		transformMatrix = s * r * t;

		Matrix4x4::Transpose(transformMatrix, transformMatrix);

		//USage���� Dynamic�� ����� �ٲ�ٴ� ��
		//����ȭ�� ���� �ɼ��̴�.
		//CPUAccessFlags�� CPU�� ���⸸ �ϰ�, GPU�� �б⸸ �Ѵ�.

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4x4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		ID3D11Device& device = Engine::Get().Device();
		HRESULT result = device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer);

		RESULT(result, TEXT("Failed to Create Transform Constant Buffer"));
	}

	Transform::Transform(const Matrix4x4& matrix)
		: transformMatrix(matrix)
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4x4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		ID3D11Device& device = Engine::Get().Device();
		HRESULT result = device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer);

		RESULT(result, TEXT("Failed to Create Transform Constant Buffer"));
	}

	Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
		: position(position), rotation(rotation), scale(scale)
	{
		Matrix4x4 s, r, t;
		Matrix4x4::Scale(scale, s);
		Matrix4x4::Rotation(rotation, r);
		Matrix4x4::Translation(position, t);
		transformMatrix = s * r * t;

		Matrix4x4::Transpose(transformMatrix, transformMatrix);

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = Matrix4x4::Stride();
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &transformMatrix;

		ID3D11Device& device = Engine::Get().Device();
		HRESULT result = device.CreateBuffer(&bufferDesc, &bufferData, &constantBuffer);

		RESULT(result, TEXT("Failed to Create Transform Constant Buffer"));
	}

	Transform::~Transform()
	{
		if (constantBuffer) {
			constantBuffer->Release();
			constantBuffer = nullptr;
		}
	}

	void Transform::Bind()
	{
		static ID3D11DeviceContext& context = Engine::Get().Context();

		Matrix4x4 s, r, t;
		Matrix4x4::Scale(scale, s);
		Matrix4x4::Rotation(rotation, r);
		Matrix4x4::Translation(position, t);
		transformMatrix = s * r * t;

		transformMatrix.Transpose();

		//2��°�� ���� ���ҽ��� ���� �ٸ� ���ҽ��� �޸𸮸� ���� ����ϸ� �ε����� ��� �� ���̴�.
		//3��°�� 
		//context.UpdateSubresource(constantBuffer, 0, nullptr, &transformMatrix, 0, 0);

		//CPU, GPU ���� ������ �� �����Ƿ� ���� �� �� ���ҽ��� ������Ʈ �ϰ� ���� Ǭ��.
		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &transformMatrix, Matrix4x4::Stride());
		context.Unmap(constantBuffer, 0);
		context.VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}