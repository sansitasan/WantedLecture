#include "CameraEntity.h"
#include "Component/CameraComponent.h"
#include "InputController.h"
#include "Engine.h"

namespace SanDX{
	CameraEntity::CameraEntity()
	{
		AddComponent(std::make_shared<CameraComponent>());
	}

	void CameraEntity::Update(float deltaTime)
	{
		Entity::Update(deltaTime);

		Move(deltaTime);
		Rotate();
	}

	void CameraEntity::Move(float deltaTime)
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

		static const float moveSpeed = 1.f;

		if (input.IsKey('A') || input.IsKey(VK_LEFT)) {
			transform.position -= transform.Right() * moveSpeed * deltaTime;
		}

		if (input.IsKey('D') || input.IsKey(VK_RIGHT)) {
			transform.position += transform.Right() * moveSpeed * deltaTime;
		}

		if (input.IsKey('W') || input.IsKey(VK_UP)) {
			transform.position += transform.Up() * moveSpeed * deltaTime;
		}

		if (input.IsKey('S') || input.IsKey(VK_DOWN)) {
			transform.position -= transform.Up() * moveSpeed * deltaTime;
		}

		if (input.IsKey('Q')) {
			transform.position += transform.Forward() * moveSpeed * deltaTime;
		}

		if (input.IsKey('E')) {
			transform.position -= transform.Forward() * moveSpeed * deltaTime;
		}
	}

	inline void CameraEntity::Rotate()
	{
		static InputController& input = InputController::Get();

		if (input.IsButton(0)) {
			static float sensitivity = 0.05f;
			transform.rotation.x += input.GetMouseDeltaY() * sensitivity;
			transform.rotation.y += input.GetMouseDeltaX() * sensitivity;
		}
	}
}
