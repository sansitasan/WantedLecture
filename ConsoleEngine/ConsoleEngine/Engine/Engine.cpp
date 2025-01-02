#include "Engine.h"
#include <Windows.h>
#include <iostream>

using namespace std;

Engine::Engine() :quit(false)
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	DWORD currentTime = timeGetTime(), previousTime = 0;
	float deltaTime;
	//Loop
	while (true) {

		if (quit) break;

		currentTime = timeGetTime();

		deltaTime = static_cast<float>(currentTime - previousTime) / 1000.0f;

		ProcessInput();
		Update(deltaTime);
		Draw();

		previousTime = currentTime;
	}
}

void Engine::ProcessInput()
{
}

void Engine::Update(float deltaTime)
{
	cout << "DeltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << '\n';
}

void Engine::Draw()
{
}
