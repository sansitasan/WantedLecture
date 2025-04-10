#include "Engine.h"
#include "Window.h"
#include "Render/Renderer.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"
#include "Resource/ModelLoader.h"
#include "InputController.h"
#include "Scene/Scene.h"

#include <iostream>

namespace SanDX {

    Engine* Engine::instance = nullptr;

    Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance)
    {
        if (Engine::instance) return;
        Engine::instance = this;
        window = std::make_shared<Window>(width, height, title, instance, WindowProc);

        inputController = std::make_unique<InputController>();
        materialLoader = std::make_unique<MaterialLoader>();
        textureLoader = std::make_unique<TextureLoader>();
        modelLoader = std::make_unique<ModelLoader>();

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
                Engine::Get().Quit();
                break;

            case WM_LBUTTONDOWN:
            {
                InputController::Get().SetButtonUpDown(0, false, true);
            }
            break;

            case WM_LBUTTONUP:
            {
                InputController::Get().SetButtonUpDown(0, true, false);
            }
            break;

            case WM_RBUTTONDOWN:
            {
                InputController::Get().SetButtonUpDown(1, false, true);
            }
            break;

            case WM_RBUTTONUP:
            {
                InputController::Get().SetButtonUpDown(1, true, false);
            }
            break;

            case WM_MBUTTONDOWN:
            {
                InputController::Get().SetButtonUpDown(2, false, true);
            }
            break;

            case WM_MBUTTONUP:
            {
                InputController::Get().SetButtonUpDown(2, true, false);
            }
            break;

            case WM_MOUSEMOVE:
            {
                int xPosition = LOWORD(lParam);
                int yPosition = HIWORD(lParam);

                InputController::Get().SetMousePosition(xPosition, yPosition);
            }
            break;

            case WM_SIZE:
            {
                if (wParam == SIZE_MINIMIZED)
                {
                    break;
                }

                uint32 width = static_cast<uint32>(LOWORD(lParam));
                uint32 height = static_cast<uint32>(HIWORD(lParam));

                Engine::Get().OnResize(width, height);
            }
            break;

            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                // MSDN 문서를 확인해 보면, 30번째 비트는 KeyUp 상태를 나타낸다고 나옴.
                bool isKeyUp = ((lParam & (static_cast<long long>(1) << 30)) != 0);

                // MSDN 문서를 확인해 보면, 31번째 비트는 KeyDown 상태를 나타낸다고 나옴.
                bool isKeyDown = ((lParam & (static_cast<long long>(1) << 31)) == 0);

                // 엔진에 키 입력 데이터 전달.
                if (isKeyUp != isKeyDown)
                {
                    // 가상 키 값.
                    uint32 vkCode = static_cast<uint32>(wParam);
                    InputController::Get().SetKeyUpDown(vkCode, isKeyUp, isKeyDown);
                }
            } break;
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

    uint32 Engine::Width() const
    {
        return window->Width();
    }

    uint32 Engine::Height() const
    {
        return window->Height();
    }

    void Engine::Run()
    {
        //int64임
        //이전에 64비트 지원하지 않을 때 사용한 것
        //이제는 long long을 사용하면 되나, 아래 함수가 이를 사용하기 때문에...
        //내부를 까보면 long long이 따로 있다.
        LARGE_INTEGER currentTime;
        LARGE_INTEGER previousTime;
        LARGE_INTEGER frequency;

        //하드웨어 타이머의 해상도 값(기준 단위)
        QueryPerformanceFrequency(&frequency);

        QueryPerformanceCounter(&currentTime);
        previousTime = currentTime;

        //프레임 계산에 사용할 변수
        float targetFrameRate = 120.f;
        //고정 프레임 속도를 사용하기 위한 변수
        float oneFrameTime = 1.f / targetFrameRate;

        MSG msg = {};
        wchar_t stat[512] = {};
        //네번째는 메시지 전달 후 삭제할것인지
        while (msg.message != WM_QUIT) {
            if (isQuit) {
                break;
            }

            //메시지가 들어왔다면
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                //메시지 번역
                TranslateMessage(&msg);
                //메시지 전달
                DispatchMessage(&msg);
            }

            else {
                QueryPerformanceCounter(&currentTime);

                float deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart)
                    / (float)frequency.QuadPart;

                if (deltaTime < oneFrameTime) continue;

                
                swprintf_s(stat, 512, TEXT("[%s] - [deltaTime: %f] [FPS: %d]"), window->Title().c_str(), deltaTime, (int)ceil(1.f / deltaTime));
                SetWindowText(window->Handle(), stat);

                if (mainScene) {
                    mainScene->BeginPlay();
                    mainScene->Update(deltaTime);
                    
                }

                renderer->Draw(mainScene);

                previousTime = currentTime;
                memset(stat, 0, sizeof(wchar_t) * 512);

                inputController->ResetInputs();
            }
        }
    }

    void Engine::SetScene(std::shared_ptr<class Scene> newScene)
    {
        mainScene = newScene;
    }

    void Engine::OnResize(uint32 width, uint32 height)
    {
        if (!window || !renderer) return;

        RECT rect;
        GetClientRect(window->Handle(), &rect);

        uint32 w = (uint32)(rect.right - rect.left);
        uint32 h = (uint32)(rect.bottom - rect.top);

        window->SetWidthHeight(w, h);

        renderer->OnResize(w, h);
    }
}