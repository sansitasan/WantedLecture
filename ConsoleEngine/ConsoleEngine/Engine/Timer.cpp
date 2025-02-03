#include "PreCompiledHeader.h"
#include "Timer.h"

Timer::Timer(float time, Delegate delegate, bool isInterval = false)
	: targetTime(time), elapsedTime(time), delegate(delegate), isInterval(isInterval) {}

Timer::~Timer()
{
	Clear();
}

bool Timer::UpdateTimer(float deltaTime)
{
	elapsedTime += deltaTime;
	if (elapsedTime >= targetTime) {
		delegate();
		if (!isInterval) {
			Clear();
			return true;
		}
		elapsedTime = 0;
		return true;
	}

	return false;
}

bool Timer::ReUse(float time, Delegate delegate, bool isInterval = false)
{
	if (elapsedTime <= 0 || delegate != nullptr) return false;
	this->isInterval = isInterval;
	targetTime = elapsedTime = time;
	this->delegate = delegate;
}

void Timer::Clear()
{
	delegate = nullptr;
	elapsedTime = 0;
	targetTime = 0;
}
