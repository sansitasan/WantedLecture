#include "Window.h"

namespace SanDX {
	Window::Window(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance, WNDPROC messageProcedure)
        : width(width), height(height), title(title), instance(instance)
    {
        //â ������ �ʿ��� ���� ����ü
        WNDCLASS wc = { };
        //ZeroMemory(&wc, sizeof(wc));

        //���ν���, �޽��� ó��
        //���Ͻð� �ƴϴ�
        wc.lpfnWndProc = messageProcedure;
        //���α׷� �ּ� ����
        wc.hInstance = instance;
        wc.lpszClassName = className.c_str();

        if (!RegisterClass(&wc)) {
            auto error = GetLastError();
            //�޽��� ��¿� std::cout�� �� �� ����
            //������ ���� â�� ���� ����ؾ� �Ѵ�
            //���� ��� â�� �̿��ϴ� �����
            OutputDebugStringA("failure window setting\n");
            //�޽��� �ڽ��� �̿��ϴ� ����� �ִ�.
            //ù �Ķ���ʹ� ���ӵ� â(���� â ���� �ٸ� â)
            //�ι�°�� �޽���
            //����°�� ����
            //�׹�°�� �ɼ�
            MessageBoxA(nullptr, "Failed to register a window class", "Error", MB_OK);

            DebugBreak();
        }

        unsigned int x = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
        unsigned int y = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;

        //â ũ�� ����
        RECT rect = { (long)0, (long)0, (long)width, (long)height };
        //��Ÿ���� ���� �ڵ�� ���ƾ� �Ѵ�
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