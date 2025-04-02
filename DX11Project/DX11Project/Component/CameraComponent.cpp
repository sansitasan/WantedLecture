#include "CameraComponent.h"
#include "Engine.h"
#include "Entity/Entity.h"
#include "Core.h"

namespace SanDX {
	CameraComponent::CameraComponent()
	{
		//cameraBuffer.viewMatrix
		//	=
		//	Matrix4x4::Translation(-owner->transform.position)
		//	* Matrix4x4::Transpose(Matrix4x4::Rotation(owner->transform.rotation));
		//
		//cameraBuffer.viewMatrix.Transpose();

		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = sizeof(CameraBuffer);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA bufferData = {};
		bufferData.pSysMem = &cameraBuffer;

		ID3D11Device& device = Engine::Get().Device();
		RESULT(device.CreateBuffer(&bufferDesc, &bufferData, &buffer), TEXT("Failed to Create Camera Buffer"));
	}

	void CameraComponent::Draw()
	{
		cameraBuffer.viewMatrix
			= 
		Matrix4x4::Translation(-owner->transform.position)
		* Matrix4x4::Transpose(Matrix4x4::Rotation(owner->transform.rotation));

		cameraBuffer.viewMatrix.Transpose();

		static ID3D11DeviceContext& context = Engine::Get().Context();

		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &cameraBuffer, Matrix4x4::Stride());
		context.Unmap(buffer, 0);
		context.VSSetConstantBuffers(1, 1, &buffer);
	}
}