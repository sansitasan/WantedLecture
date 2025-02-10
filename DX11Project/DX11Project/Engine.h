#pragma once
#include <memory>
#include <Windows.h>
#include "Type.h"
#include <string>

namespace SanDX {
	//���ҽ� ���, application �ܰ��� â��.
	class Engine {
	public:
		Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance);
		virtual ~Engine();

		//������ �޽��� ó�� ����
		static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

		//�̱��� ���� �Լ�
		static Engine& Get();

		void Run();

	protected:
		//â ��ü
		std::shared_ptr<class Window> window;

		//������ ��ü
		std::shared_ptr<class Renderer> renderer;

		//�̱��� ��ü
		static Engine* instance;
	};
}