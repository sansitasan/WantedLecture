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

    //â�� ���õ� �޽����� ó���ϴ� �ݹ� �Լ�
    //��ǲ, Ȱ��ȭ ���� �̺�Ʈ�� ���� ������ �����ش޶�� ��û�ϴ� ��
    LRESULT Engine::WindowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        //�޽��� ó��
        switch (message) {
            //â ������ ����
            case WM_DESTROY:
                //���α׷� ���� �޽��� ����
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
                // MSDN ������ Ȯ���� ����, 30��° ��Ʈ�� KeyUp ���¸� ��Ÿ���ٰ� ����.
                bool isKeyUp = ((lParam & (static_cast<long long>(1) << 30)) != 0);

                // MSDN ������ Ȯ���� ����, 31��° ��Ʈ�� KeyDown ���¸� ��Ÿ���ٰ� ����.
                bool isKeyDown = ((lParam & (static_cast<long long>(1) << 31)) == 0);

                // ������ Ű �Է� ������ ����.
                if (isKeyUp != isKeyDown)
                {
                    // ���� Ű ��.
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
        //int64��
        //������ 64��Ʈ �������� ���� �� ����� ��
        //������ long long�� ����ϸ� �ǳ�, �Ʒ� �Լ��� �̸� ����ϱ� ������...
        //���θ� ��� long long�� ���� �ִ�.
        LARGE_INTEGER currentTime;
        LARGE_INTEGER previousTime;
        LARGE_INTEGER frequency;

        //�ϵ���� Ÿ�̸��� �ػ� ��(���� ����)
        QueryPerformanceFrequency(&frequency);

        QueryPerformanceCounter(&currentTime);
        previousTime = currentTime;

        //������ ��꿡 ����� ����
        float targetFrameRate = 120.f;
        //���� ������ �ӵ��� ����ϱ� ���� ����
        float oneFrameTime = 1.f / targetFrameRate;

        MSG msg = {};
        wchar_t stat[512] = {};
        //�׹�°�� �޽��� ���� �� �����Ұ�����
        while (msg.message != WM_QUIT) {
            if (isQuit) {
                break;
            }

            //�޽����� ���Դٸ�
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                //�޽��� ����
                TranslateMessage(&msg);
                //�޽��� ����
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