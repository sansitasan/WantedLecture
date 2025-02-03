#pragma once
#include "Core.h"
#include <iostream>
#include <functional>

class ENGINE_API Timer {
	using Delegate = std::function<void()>;
public:
	Timer() = delete;
	Timer(Timer&&) = delete;
	Timer(float time, Delegate delegate, bool isInterval);
	~Timer();
	bool UpdateTimer(float deltaTime);
	bool ReUse(float time, Delegate delegate, bool isInterval);

private:
	void Clear();

private:
	float targetTime;
	float elapsedTime;
	bool isInterval;
	Delegate delegate;
};