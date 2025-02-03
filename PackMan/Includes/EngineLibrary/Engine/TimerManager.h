#pragma once
#include <vector>
#include <new>
#include <map>
#include <Memory/MemoryPool.h>
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
	MemoryPool<Timer> timerMemory;
};