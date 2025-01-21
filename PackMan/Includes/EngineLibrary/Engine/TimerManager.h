#pragma once
#include <vector>
#include <new>
#include <map>
#include "Timer.h"

class TimerManager {
	using Delegate = std::function<void()>;

public:
	TimerManager();

	~TimerManager();

	void AddTimer(const Delegate& delegate, float time, bool isInterval, size_t id);

	void DeleteTimer(size_t id, const Delegate& delegate);

	void DeleteEntityTimers(size_t id);

	void Update(float deltaTime);

private:

	void Swap(int i, int j);

	void MemoryAllocate();

private:
	int count = 0;
	int capacity = 4;
	Timer* timerMemory;
};