#pragma once
#include <memory>
#include <Windows.h>
#include "Type.h"
#include <string>
#include <d3d11.h>

namespace SanDX {
	//리소스 담당, application 단계의 창고.
	class Engine {
	public:
		Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance);
		virtual ~Engine();

		//윈도우 메시지 처리 루프
		static LRESULT CALLBACK WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

		//싱글톤 접근 함수
		static Engine& Get();
		ID3D11Device& Device() const;
		ID3D11DeviceContext& Context() const;

		void Run();

	protected:
		//창 객체
		std::shared_ptr<class Window> window;

		//렌더러 객체
		std::shared_ptr<class Renderer> renderer;

		//싱글톤 객체
		static Engine* instance;
	};
}