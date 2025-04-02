#include "Engine.h"
#include "Window.h"
#include "Render/Renderer.h"
#include "Resource/MaterialLoader.h"
#include "Resource/TextureLoader.h"
#include "Resource/ModelLoader.h"
#include "Scene/Scene.h"

#include <iostream>

namespace SanDX {

    Engine* Engine::instance = nullptr;

    Engine::Engine(uint32 width, uint32 height, const std::wstring& title, HINSTANCE instance)
    {
        if (Engine::instance) return;
        Engine::instance = this;
        window = std::make_shared<Window>(width, height, title, instance, WindowProc);

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
        //�׹�°�� �޽��� ���� �� �����Ұ�����
        while (msg.message != WM_QUIT) {
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

                //if (deltaTime < oneFrameTime) continue;

                std::cout 
                    << "deltaTime: " << deltaTime 
                    << " | OneFrameTime: " << oneFrameTime 
                    << " | FPS: " << (int)ceil(1.f / deltaTime) << '\n';

                if (mainScene) {
                    mainScene->BeginPlay();
                    mainScene->Update(deltaTime);
                    
                }

                renderer->Draw(mainScene);

                previousTime = currentTime;
            }
        }
    }

    void Engine::SetScene(std::shared_ptr<class Scene> newScene)
    {
        mainScene = newScene;
    }
}