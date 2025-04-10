#include "InputController.h"

namespace SanDX {
	InputController* InputController::instance = nullptr;

	InputController::InputController()
	{
		instance = this;
	}

	//����Ʈ �����͸� �� �� ��Ȥ default�� ����ϸ� ������ �� �� �ִ�.
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