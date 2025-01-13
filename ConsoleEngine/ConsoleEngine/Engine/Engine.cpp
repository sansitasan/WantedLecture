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
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	memset(clearArr, ' ', (MAXX - 1) * sizeof(char));
	delegateKeyDown = std::vector<std::vector<std::function<void()>>>(KEYCOUNT, std::vector<std::function<void()>>());
	delegateKey = std::vector<std::vector<std::function<void()>>>(KEYCOUNT, std::vector<std::function<void()>>());
	delegateKeyUp = std::vector<std::vector<std::function<void()>>>(KEYCOUNT, std::vector<std::function<void()>>());
	instance = this;
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
			mainScene->ProcessAddedAndDestroyedEntity();
		}

		shouldUpdate = true;

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
	SetCursorPosition(static_cast<int>(position.GetX()), static_cast<int>(position.GetY()));
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

void Engine::SubscribeGetKey(std::function<void()> delegate, int key)
{
	delegateKey[key].push_back(delegate);
}

void Engine::SubscribeGetKeyDown(std::function<void()> delegate, int key)
{
	delegateKeyDown[key].push_back(delegate);
}

void Engine::SubscribeGetKeyUp(std::function<void()> delegate, int key)
{
	delegateKeyUp[key].push_back(delegate);
}

void Engine::UnSubscribeGetKey(std::function<void()> delegate, int key)
{
	auto& list = delegateKey[key];
	const auto& it = std::find_if(list.begin(), list.end(), [&](const std::function<void()>& item) {
		return item.target<void()>() == delegate.target<void()>();
		});

	if (it == list.end()) return;

	list.erase(it);
}

void Engine::UnSubscribeGetKeyDown(std::function<void()> delegate, int key)
{
	auto& list = delegateKeyDown[key];
	const auto& it = std::find_if(list.begin(), list.end(), [&](const std::function<void()>& item) {
		return item.target<void()>() == delegate.target<void()>();
		});

	if (it == list.end()) return;

	list.erase(it);
}

void Engine::UnSubscribeGetKeyUp(std::function<void()> delegate, int key)
{
	auto& list = delegateKeyUp[key];
	const auto& it = std::find_if(list.begin(), list.end(), [&](const std::function<void()>& item) {
		return item.target<void()>() == delegate.target<void()>();
		});

	if (it == list.end()) return;

	list.erase(it);
}

void Engine::ProcessInput()
{
	for (int i = 0; i < KEYCOUNT; ++i) {
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
		if (GetKeyDown(i)) {
			for (int j = 0; j < delegateKeyDown[i].size(); ++j) {
				delegateKeyDown[i][j]();
			}
		}

		if (GetKey(i)) {
			for (int j = 0; j < delegateKey[i].size(); ++j) {
				delegateKey[i][j]();
			}
		}

		if (GetKeyUp(i)) {
			for (int j = 0; j < delegateKeyUp[i].size(); ++j) {
				delegateKeyUp[i][j]();
			}
		}
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
	for (int i = 0; i < MAXY; ++i) {
		Log("                                                                                                                        \n");
	}
	Log("                                                                                                                        ");
	SetCursorPosition(0, 0);
}