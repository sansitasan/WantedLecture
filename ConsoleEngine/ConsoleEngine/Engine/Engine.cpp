#include "PreCompiledHeader.h"
#include "Scene/Scene.h"
#include "Math/Vector/Vector2.h"
#include <Windows.h>
#include <iostream>
#include "Entity/Entity.h"
#include "Engine.h"

using namespace std;

Engine* Engine::instance = nullptr;

Engine::Engine() :quit(false), mainScene(nullptr), targetFrameRate(60), targetOneFrameTime(1 / 60)
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
	float deltaTime;

	targetOneFrameTime = 1 / targetFrameRate;
	//Loop
	while (true) {

		if (quit) break;
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		if (deltaTime < targetOneFrameTime) continue;

		//입력상태 확인
		ProcessInput();

		//업데이트 가능한 상태에서만 업데이트를 처리해야 한다.
		if (shouldUpdate) {
			Update(deltaTime);
			Draw();
		}

		previousTime = currentTime;

		if (mainScene) {
			mainScene->DestroyEntity();
		}

		shouldUpdate = true;

		//Sleep(10);
	}
}

void Engine::LoadScene(Scene* newScene)
{
	mainScene = newScene;
}

void Engine::AddEntity(Entity* entity)
{
	if (!mainScene) return;

	shouldUpdate = false;
	mainScene->AddEntity(entity);
}

void Engine::DestroyEntity(Entity* entity)
{
	if (!mainScene) return;

	shouldUpdate = false;
	entity->Destroy();
}

void Engine::SetCursorType(ECursorType type)
{
	CONSOLE_CURSOR_INFO info = {};

	switch (type) {
		case ECursorType::NoCursor:
			info.dwSize = 1;
			info.bVisible = FALSE;
			break;

		case ECursorType::NormalCursor:
			info.dwSize = 20;
			info.bVisible = TRUE;
			break;

		case ECursorType::SolidCursor:
			info.dwSize = 100;
			info.bVisible = TRUE;
			break;
	}

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.GetX(), position.GetY());
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetFrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1 / targetFrameRate;
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
	(this->*QuitEngine)();
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

void Engine::Update(float deltaTime)
{
	if (!mainScene) return;

	mainScene->Update(deltaTime);
}

void Engine::Draw()
{
	Clear();

	if (!mainScene) return;
	mainScene->Draw();
}

void Engine::Clear()
{
	SetCursorPosition(0, 0);
	int height = 25;
	for (int i = 0; i < height; ++i) {
		Log("                              \n");
	}
	SetCursorPosition(0, 0);
}
