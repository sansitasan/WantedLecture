#include "PreCompiledHeader.h"
#include "TimerManager.h"

TimerManager::TimerManager() {
	}

TimerManager::~TimerManager() {
	timerMemory.Clear();
}

void TimerManager::AddTimer(const Delegate& delegate, float time, bool isInterval, size_t id) {
	if (time <= 0) {
		__debugbreak();
		return;
	}

	timerMemory.MakeItem(delegate, time, isInterval, id);
}

void TimerManager::DeleteTimer(size_t id, const Delegate& delegate) {
	for (int i = 0; i < timerMemory.size(); ++i) {
		if (timerMemory[i]->GetID() != id || !timerMemory[i]->IsSameDelegate(delegate)) continue;
		timerMemory.erase(i);
		return;
	}
}

void TimerManager::DeleteEntityTimers(size_t id)
{
	for (int i = 0; i < timerMemory.size(); ++i) {
		if (timerMemory[i]->GetID() != id) continue;
		timerMemory.erase(i);
		--i;
	}
}

void TimerManager::Update(float deltaTime) {
	for (int i = 0; i < timerMemory.size();) {
		if (timerMemory[i]->UpdateTimer(deltaTime) && !timerMemory[i]->IsInterval()) {
			timerMemory.erase(i);
			continue;
		}
		++i;
	}
}