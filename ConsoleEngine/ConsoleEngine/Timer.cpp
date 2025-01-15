#include "PreCompiledHeader.h"
#include "Timer.h"

Timer::Timer(float time, Delegate delegate)
	: decideTime(time), remainTime(time), delegate(delegate) {}

Timer::~Timer()
{
	Clear();
}

bool Timer::UpdateTimer(float deltaTime)
{
	remainTime -= deltaTime;
	if (remainTime <= 0) {
		delegate();
		Clear();
		return true;
	}

	return false;
}

bool Timer::ReUse(float time, Delegate delegate)
{
	if (remainTime <= 0 || delegate != nullptr) return false;
	decideTime = remainTime = time;
	this->delegate = delegate;
}

void Timer::Clear()
{
	delegate = nullptr;
	remainTime = 0;
	decideTime = 0;
}
