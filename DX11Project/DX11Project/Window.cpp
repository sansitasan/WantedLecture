#include "Window.h"

namespace SanDX {
	Window::Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure)
        : width(width), height(height), title(title), instance(instance)
    {
        //창 생성에 필요한 정보 구조체
        WNDCLASS wc = { };
        //ZeroMemory(&wc, sizeof(wc));

        //프로시저, 메시지 처리
        //프록시가 아니다
        wc.lpfnWndProc = messageProcedure;
        //프로그램 주소 전달
        wc.hInstance = instance;
        wc.lpszClassName = className.c_str();

        if (!RegisterClass(&wc)) {
            auto error = GetLastError();
            //메시지 출력에 std::cout을 쓸 수 없다
            //쓰려면 직접 창을 만들어서 사용해야 한다
            //따라서 출력 창을 이용하는 방법과
            OutputDebugStringA("failure window setting\n");
            //메시지 박스를 이용하는 방법이 있다.
            //첫 파라미터는 종속된 창(현재 창 외의 다른 창)
            //두번째가 메시지
            //세번째가 제목
            //네번째는 옵션
            MessageBoxA(nullptr, "Failed to register a window class", "Error", MB_OK);

            DebugBreak();
        }

        unsigned int x = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
        unsigned int y = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

        //창 크기 조정
        RECT rect = { (long)0, (long)0, (long)width, (long)height };
        //스타일은 밑의 핸들과 같아야 한다
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

        unsigned int windowWidth = rect.right - rect.left;
        unsigned int windowHeight = rect.bottom - rect.top;

        handle = CreateWindow(
            className.c_str(),              // Window class
            title.c_str(),                  // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position x, y, width, height
            x, y, 
            windowWidth, windowHeight,

            nullptr,                        // Parent window    
            nullptr,                        // Menu
            instance,                      // Instance handle
            nullptr                         // Additional application data
        );

        if (!handle)
        {
            OutputDebugStringA("failure window create\n");

            MessageBoxA(nullptr, "Failed to create a window class", "Error", MB_OK);

            DebugBreak();
            return;
        }

        ShowWindow(handle, SW_SHOW);
        UpdateWindow(handle);
	}

	Window::~Window()
	{
        UnregisterClass(className.c_str(), instance);
	}

	inline void Window::SetWidthHeight(uint32 width, uint32 height)
	{
		this->width = width;
		this->height = height;
	}
}