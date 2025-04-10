#pragma once

#include "Math/Vector2.h"

namespace SanDX {
	struct KeyInputData {
		bool isKeyDown = false;
		bool isKeyUp = false;
		bool isKey = false;

		void SetKeyUpDown(bool isKeyUp, bool isKeyDown) {
			this->isKeyUp = isKeyUp;
			this->isKeyDown = isKeyDown;

			isKey = isKeyDown && !isKeyUp;
		}
	};

	struct MouseInputData {
		bool isButtonDown = false;
		bool isButtonUp = false;
		bool isButton = false;

		void SetButtonUpDown(bool isButtonUp, bool isButtonDown) {
			this->isButtonUp = isButtonUp;
			this->isButtonDown = isButtonDown;

			isButton = isButtonDown && !isButtonUp;
		}
	};

	class InputController {
	public:
		InputController();
		~InputController();

		inline bool IsKeyDown(unsigned int keyCode) { return keyInputData[keyCode].isKeyDown; }
		inline bool IsKeyUp(unsigned int keyCode) { return keyInputData[keyCode].isKeyUp; }
		inline bool IsKey(unsigned int keyCode) { return keyInputData[keyCode].isKey; }

		inline bool IsButtonDown(unsigned int Button) { return mouseInputData[Button].isButtonDown; }
		inline bool IsButtonUp(unsigned int Button) { return mouseInputData[Button].isButton; }
		inline bool IsButton(unsigned int Button) { return mouseInputData[Button].isButton; }

		void ResetInputs();

		inline Vector2 GetMousePosition() { return mousePosition; }
		inline Vector2 GetMouseDelta() { return mousePosition - mousePreviousPosition; }
		inline float GetMouseDeltaX() { return mousePosition.GetX() - mousePreviousPosition.GetX(); }
		inline float GetMouseDeltaY() { return mousePosition.GetY() - mousePreviousPosition.GetY(); }

		inline void SetKeyUpDown(unsigned int keyCode, bool isKeyUp, bool isKeyDown) { keyInputData[keyCode].SetKeyUpDown(isKeyUp, isKeyDown); }
		inline void SetButtonUpDown(unsigned int button, bool isButtonUp, bool isButtonDown) { mouseInputData[button].SetButtonUpDown(isButtonUp, isButtonDown); }
		inline void SetMousePosition(int x, int y) {
			mousePreviousPosition = mousePosition;
			mousePosition = Vector2((float)x, (float)y);
		}

		//안전성 확보가 어렵다
		//초기화가 이미 되어 있는지
		static InputController& Get();
	private:
		KeyInputData keyInputData[256] = {};
		MouseInputData mouseInputData[3] = {};

		Vector2 mousePosition = Vector2::Zero;
		Vector2 mousePreviousPosition = Vector2::Zero;

		static InputController* instance;
	};
}