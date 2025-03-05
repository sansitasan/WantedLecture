#include "Engine.h"
#include "Window.h"
#include "Render/Renderer.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"

namespace SanDX {

    Engine* Engine::instance = nullptr;

    Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance)
    {
        if (Engine::instance) return;
        Engine::instance = this;
        window = std::make_shared<Window>(width, height, title, instance, WindowProc);

        materialLoader = std::make_unique<MaterialLoader>();
        textureLoader = std::make_unique<TextureLoader>();

        renderer = std::make_shared<Renderer>(width, height, window->Handle());
    }

    Engine::~Engine()
    {
    }

    //창에 관련된 메시지를 처리하는 콜백 함수
    //인풋, 활성화 등의 이벤트가 있을 때마다 전달해달라고 요청하는 것
    LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        //메시지 처리
        switch (message) {
            //창 삭제시 실행
        case WM_DESTROY:
            //프로그램 종료 메시지 발행
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(handle, message, wParam, lParam);
    }

    Engine& Engine::Get()
    {
        return *instance;
    }

    ID3D11Device& Engine::Device() const
    {
        return *renderer->device;
    }

    ID3D11DeviceContext& Engine::Context() const
    {
        return *renderer->context;
    }

    void Engine::Run()
    {
        MSG msg = {};
        //네번째는 메시지 전달 후 삭제할것인지
        while (msg.message != WM_QUIT) {
            //메시지가 들어왔다면
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                //메시지 번역
                TranslateMessage(&msg);
                //메시지 전달
                DispatchMessage(&msg);
            }

            else {
                //엔진 루프
                renderer->Draw();
            }
        }
    }
}