#pragma once

#include <Windows.h>
#include <string>
#include "Type.h"

namespace SanDX {
	class Window {
	public:
		Window(uint32 width, uint32 height, 
			const std::wstring& title, 
			HINSTANCE instance, WNDPROC messageProcedure);

		~Window();

		inline const uint32 Width() const { return width; }
		inline const uint32 Height() const { return height; }
		inline HWND Handle() const { return handle; }

		inline void SetWidthHeight(uint32 width, uint32 height);

	private:
		unsigned int width = 0;
		unsigned int height = 0;
		std::wstring title = nullptr;
		std::wstring className = TEXT("DX Demo");
		HWND handle = nullptr;
		HINSTANCE instance = nullptr;
	};
}