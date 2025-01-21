#include "PreCompiledHeader.h"
#include "TimerManager.h"

TimerManager::TimerManager() {
		timerMemory = new Timer[capacity];
		memset(timerMemory, 0, capacity * sizeof(Timer));
	}

TimerManager::~TimerManager() {
	for (int i = 0; i < count; ++i) {
		timerMemory[i].Clear();
	}

	if (timerMemory) {
		delete[] timerMemory;
		timerMemory = nullptr;
	}
}

void TimerManager::AddTimer(const Delegate& delegate, float time, bool isInterval, size_t id) {
	if (time <= 0) {
		__debugbreak();
		return;
	}

	if (capacity == count) MemoryAllocate();
	size_t test = reinterpret_cast<size_t>(&timerMemory[count]);

	new (&timerMemory[count++]) Timer(delegate, time, isInterval, id);
}

void TimerManager::DeleteTimer(size_t id, const Delegate& delegate) {
	for (int i = 0; i < count; ++i) {
		if (timerMemory[i].GetID() != id || !timerMemory[i].IsSameDelegate(delegate)) continue;
		timerMemory[i].Clear();
		if (i == --count) return;
		Swap(i, count);
		break;
	}
}

void TimerManager::DeleteEntityTimers(size_t id)
{
	for (int i = 0; i < count; ++i) {
		if (timerMemory[i].GetID() != id) continue;
		timerMemory[i].Clear();
		if (i == --count) return;
		Swap(i, count);
	}
}

void TimerManager::Update(float deltaTime) {
	for (int i = 0; i < count;) {
		if (timerMemory[i].UpdateTimer(deltaTime) && !timerMemory[i].IsInterval()) {
			if (i == --count) return;
			Swap(i, count);
			continue;
		}
		++i;
	}
}

void TimerManager::TimerManager::Swap(int i, int j) {
	Timer& temp = timerMemory[i];
	timerMemory[i] = timerMemory[j];
	timerMemory[j] = temp;
}

void TimerManager::MemoryAllocate() {
	size_t size = sizeof(Timer) * capacity;
	Timer* temp = new Timer[capacity];
	memcpy_s(temp, size << 1, timerMemory, size);
	free(timerMemory);
	timerMemory = temp;

	capacity <<= 1;
}