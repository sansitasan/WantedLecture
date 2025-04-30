#include "CameraComponent.h"
#include "Engine.h"
#include "Entity/Entity.h"
#include "InputController.h"
#include "Core.h"

namespace SanDX {
	CameraComponent::CameraComponent()
	{
		cameraBuffer.projectionMatrix = Matrix4x4::Perspective(
			90.f,
			(float)Engine::Get().Width(),
			(float)Engine::Get().Height(),
			0.1f,
			100.f
		);
		cameraBuffer.projectionMatrix.Transpose();


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

	void CameraComponent::Update(float deltaTime)
	{
		static InputController& input = InputController::Get();
		if (input.IsKeyDown(VK_ESCAPE)) {
			if (MessageBox(nullptr, 
				TEXT("Want to Quit?"), 
				TEXT("Quit Engine"), 
				MB_YESNO) == IDYES) {
				Engine::Get().Quit();
			}
		}

		if (input.IsKey('A') || input.IsKey(VK_LEFT)) {
			owner->transform.position.x -= deltaTime;
		}

		if (input.IsKey('D') || input.IsKey(VK_RIGHT)){
			owner->transform.position.x += deltaTime;
		}

		if (input.IsKey('W') || input.IsKey(VK_UP)) {
			owner->transform.position.y += deltaTime;
		}

		if (input.IsKey('S') || input.IsKey(VK_DOWN)) {
			owner->transform.position.y -= deltaTime;
		}

		if (input.IsKey('Q')) {
			owner->transform.position.z += deltaTime;
		}

		if (input.IsKey('E')) {
			owner->transform.position.z -= deltaTime;
		}
	}

	void CameraComponent::Draw()
	{
		cameraBuffer.viewMatrix
			= 
		Matrix4x4::Translation(-owner->transform.position)
		* Matrix4x4::Transpose(Matrix4x4::Rotation(owner->transform.rotation));

		cameraBuffer.viewMatrix.Transpose();

		cameraBuffer.projectionMatrix = Matrix4x4::Perspective(
			90.f,
			(float)Engine::Get().Width(),
			(float)Engine::Get().Height(),
			0.1f,
			100.f
		);
		cameraBuffer.projectionMatrix.Transpose();

		static ID3D11DeviceContext& context = Engine::Get().Context();

		D3D11_MAPPED_SUBRESOURCE resource = {};
		context.Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		memcpy(resource.pData, &cameraBuffer, sizeof(CameraBuffer));
		context.Unmap(buffer, 0);
		context.VSSetConstantBuffers(1, 1, &buffer);
	}
}