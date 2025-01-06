#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Scene/Scene.h"
#include <Windows.h>
#include <iostream>

using namespace std;

Engine* Engine::instance = nullptr;

Engine::Engine() :quit(false), mainScene(nullptr)
{
	memset(delegateKey, 0, sizeof(int) * KEYCOUNT);
	memset(delegateKeyDown, 0, sizeof(int) * KEYCOUNT);
	memset(delegateKeyUp, 0, sizeof(int) * KEYCOUNT);
	instance = this;
	//SubscribeGetKeyDown(, VK_ESCAPE);
}

Engine::~Engine()
{
	SafeDelete(mainScene);
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::Run()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart, previousTime = 0;
	double deltaTime;

	double targetFrameRate = 60.0f, targetOneFrameTime = 1 / targetFrameRate;
	//Loop
	while (true) {

		if (quit) break;
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		deltaTime = static_cast<double>(currentTime - previousTime) / 
			static_cast<double>(frequency.QuadPart);

		if (deltaTime < targetOneFrameTime) continue;

		//입력상태 확인
		ProcessInput();
		Update(deltaTime);
		Draw();

		previousTime = currentTime;

		//Sleep(10);
	}
}

void Engine::LoadScene(Scene* newScene)
{
	mainScene = newScene;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitEngine()
{
	quit = true;
}

void Engine::SubscribeGetKey(void (*delegate)(), int key)
{
	delegateKey[key] = delegate;
}

void Engine::SubscribeGetKeyDown(void(*delegate)(), int key)
{
	delegateKeyDown[key] = delegate;
}

void Engine::SubscribeGetKeyUp(void(*delegate)(), int key)
{
	delegateKeyUp[key] = delegate;
}

void Engine::UnSubscribeGetKey(void(*delegate)(), int key)
{
	delegateKey[key] = nullptr;
}

void Engine::UnSubscribeGetKeyDown(void(*delegate)(), int key)
{
	delegateKeyDown[key] = nullptr;
}

void Engine::UnSubscribeGetKeyUp(void(*delegate)(), int key)
{
	delegateKeyUp[key] = nullptr;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < KEYCOUNT; ++i) {
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(double deltaTime)
{
	if (GetKeyDown(VK_ESCAPE)) QuitEngine();
	if (!mainScene) return;

	mainScene->Update(deltaTime);
	//cout << "DeltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << '\n';
}

void Engine::Draw()
{
	if (!mainScene) return;
	mainScene->Draw();
}
