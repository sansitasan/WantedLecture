#include "InputController.h"

namespace SanDX {
	InputController* InputController::instance = nullptr;

	InputController::InputController()
	{
		instance = this;
	}

	//스마트 포인터를 쓸 때 간혹 default를 사용하면 오류가 날 수 있다.
	InputController::~InputController()
	{
	}

	void InputController::ResetInputs()
	{
		for (KeyInputData& data : keyInputData)
		{
			data.isKeyUp = false;
			data.isKeyDown = false;
		}

		for (MouseInputData& data : mouseInputData)
		{
			data.isButtonDown = false;
			data.isButtonUp = false;
		}

		mousePreviousPosition = mousePosition;
	}

	InputController& InputController::Get()
	{
		return *instance;
	}
}