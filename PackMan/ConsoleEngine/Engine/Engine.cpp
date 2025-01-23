#include "PreCompiledHeader.h"
#include "Render/ScreenBuffer.h"
#include "Scene/Scene.h"
#include "Math/Vector/Vector2.h"
#include <Windows.h>
#include <iostream>
#include "Entity/Entity.h"
#include <time.h>
#include "TimerManager.h"
#include "Engine.h"

using namespace std;

Engine* Engine::instance = nullptr;

BOOL WINAPI MessageProcessor(DWORD message)
{
	switch (message)
	{
	case CTRL_CLOSE_EVENT:
		Engine::Get().QuitEngine();
		return true;

	default:
		return false;
	}
}

Engine::Engine() 
	: quit(false), mainScene(nullptr), targetFrameRate(60), 
	targetOneFrameTime(1 / 60), screenSize(35, 40)
{
	timerManager = new TimerManager();
	srand((unsigned int)time(nullptr));
	int sizeX = (int)screenSize.GetX();
	int sizeY = (int)screenSize.GetY();

	SetConsoleSizeAndLock(sizeX, sizeY);

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	delegateKeyDown = Delegate(KEYCOUNT, std::vector<pair<Entity*, std::function<void()>>>());
	delegateKey = Delegate(KEYCOUNT, std::vector<pair<Entity*, std::function<void()>>>());
	delegateKeyUp = Delegate(KEYCOUNT, std::vector<pair<Entity*, std::function<void()>>>());
	instance = this;

	imageBuffer = new CHAR_INFO[(sizeX + 1) * sizeY + 1];

	ClearImageBuffer();
	
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	if (!GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi)) {
		std::cerr << "Failed to get current console font info." << std::endl;
		return;
	}
	cfi.nFont = 0;
	cfi.dwFontSize.X = 18;
	cfi.dwFontSize.Y = 18;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi)) {
		std::cerr << "Failed to set console font." << std::endl;
		return;
	}

	COORD size = { (short)sizeX, (short)sizeY };
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), size);
	renderTargets[1] = new ScreenBuffer(size, cfi);
	// 스왑 버퍼.
	Present();

	// 콘솔 창 이벤트 콜백 함수 등록.
	SetConsoleCtrlHandler(MessageProcessor, true);
}

Engine::~Engine()
{
	delete timerManager;
	SafeDelete(&mainScene);
	delete[] imageBuffer;

	delete renderTargets[0];
	delete renderTargets[1];

	for (int i = 0; i < KEYCOUNT; ++i) {
		delegateKeyDown[i].clear();
		delegateKeyUp[i].clear();
		delegateKey[i].clear();
	}
	delegateKeyDown.clear();
	delegateKeyUp.clear();
	delegateKey.clear();
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

	int64_t currentTime = time.QuadPart, previousTime = currentTime;
	deltaTime = 10.f;

	targetOneFrameTime = 1 / targetFrameRate;
	//Loop

	while (deltaTime > .1f) {
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		previousTime = currentTime;
	}

	while (true) {

		if (quit) break;
		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		if (deltaTime < targetOneFrameTime) continue;

		ProcessInput();
		timerManager->Update(deltaTime);
		Update(deltaTime);
		Draw();

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

	//shouldUpdate = false;
	timerManager->DeleteEntityTimers(entity->GetUniqueID());
	entity->Destroy();
	mainScene->AddDeleteEntityQueue(entity);
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

void Engine::SetTimer(std::function<void()> delegate, float time, bool isInterval, size_t id)
{
	timerManager->AddTimer(delegate, time, isInterval, id);
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

void Engine::SubscribeGetKey(std::function<void()> delegate, Entity* entity, int key)
{
	delegateKey[key].push_back(make_pair(entity, delegate));
}

void Engine::SubscribeGetKeyDown(std::function<void()> delegate, Entity* entity, int key)
{
	delegateKeyDown[key].push_back(make_pair(entity, delegate));
}

void Engine::SubscribeGetKeyUp(std::function<void()> delegate, Entity* entity, int key)
{
	delegateKeyUp[key].push_back(make_pair(entity, delegate));
}

void Engine::UnSubscribeGetKey(std::function<void()> delegate, int key)
{
	UnSubscribe(delegateKey, delegate, key);
}

void Engine::UnSubscribeGetKeyDown(std::function<void()> delegate, int key)
{
	UnSubscribe(delegateKeyDown, delegate, key);
}

void Engine::UnSubscribeGetKeyUp(std::function<void()> delegate, int key)
{
	UnSubscribe(delegateKeyUp, delegate, key);
}

void Engine::SetConsoleSizeAndLock(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWndConsole = GetConsoleWindow();

	COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

	//LONG style = GetWindowLong(hWndConsole, GWL_STYLE);
	//style &= ~WS_MAXIMIZEBOX;
	//style &= ~WS_SIZEBOX;
	//SetWindowLong(hWndConsole, GWL_STYLE, style);

	//RECT rect;
	//GetWindowRect(hWndConsole, &rect);
	//MoveWindow(hWndConsole, rect.left, rect.top, width * 8, height * 16, TRUE);
}

void Engine::UnSubscribe(Delegate& delegateVector, std::function<void()> delegate, int key)
{
	int num = 0;
	for (int i = 0; i < delegateVector[key].size(); ++i) {
		if (delegateVector[key][i].second.target<void()>() == delegate.target<void()>()) {
			num = i;
			delegateVector[key].erase(delegateVector[key].begin() + num);
			return;
		}
	}
	std::cout << "is not Exist!\n";
	__debugbreak();
}

void Engine::DelegateInvoke(Delegate& delegateVector, int key)
{
	for (int j = 0; j < delegateVector[key].size(); ++j) {
		if (!delegateVector[key][j].first) {
			delegateVector[key].erase(delegateVector[key].begin() + j);
			continue;
		}
		if (!delegateVector[key][j].first->IsActive()) continue;

		delegateVector[key][j].second();
	}
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
	if (GetKey(VK_ESCAPE)) QuitEngine();
	if (!mainScene) return;

	for (int i = 0; i < KEYCOUNT; ++i) {
		if (GetKeyDown(i)) {
			DelegateInvoke(delegateKeyDown, i);
		}

		if (GetKey(i)) {
			DelegateInvoke(delegateKey, i);
		}

		if (GetKeyUp(i)) {
			DelegateInvoke(delegateKeyUp, i);
		}
	}
	mainScene->Update(deltaTime);
}

void Engine::Draw(const Vector2& position, const char* image, Color color)
{
	Vector2 pos = position;
	for (int ix = 0; ix < (int)strlen(image); ++ix)
	{
		int index = ((int)pos.GetY() * (int)screenSize.GetX()) + (int)pos.GetX() + ix;
		imageBuffer[index].Char.AsciiChar = image[ix];
		imageBuffer[index].Attributes = (unsigned long)color;
	}
}

void Engine::CancelTimer(std::function<void()> delegate, size_t id)
{
	timerManager->DeleteTimer(id, delegate);
}

void Engine::CancelAllTimer(size_t id)
{
	timerManager->DeleteEntityTimers(id);
}

void Engine::Draw()
{
	Clear();

	// 레벨 그리기.
	if (mainScene != nullptr)
	{
		mainScene->Draw();
	}

	// 백버퍼에 데이터 쓰기.
	GetRenderer()->Draw(imageBuffer);
	
	// 프론트<->백 버퍼 교환.
	Present();
}

void Engine::Clear()
{
	ClearImageBuffer();
	GetRenderer()->Clear();
}

void Engine::Present()
{
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

void Engine::ClearImageBuffer()
{
	for (int y = 0; y < screenSize.GetY(); ++y)
	{
		for (int x = 0; x < screenSize.GetX() + 1; ++x)
		{
			auto& buffer = imageBuffer[(y * ((int)screenSize.GetX() + 1)) + x];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = 0;
		}

		auto& buffer = imageBuffer[(y * ((int)screenSize.GetX() + 1)) + (int)screenSize.GetX()];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = 0;
	}

	auto& buffer = imageBuffer[((int)screenSize.GetX() + 1) * (int)screenSize.GetY()];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = 0;
}
