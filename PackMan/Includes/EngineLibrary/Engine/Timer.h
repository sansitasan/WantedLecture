#pragma once
#include "Core.h"
#include <functional>

//truct Conditions {
//
//;
//
//lass Timer {
//	using Delegate = std::function<void()>;
//	using Condition = bool(*)(float);
//ublic:
//	Timer()
//		: delegate(nullptr), isInterval(false), id(0), condition(nullptr) {
//	};
//
//	Timer(const Delegate& delegate, size_t id, bool isInterval, Condition condition)
//		: delegate(delegate), isInterval(isInterval), id(id), condition(condition) {
//	}
//	
//	bool UpdateTimer(float deltaTime) {
//		if (condition(deltaTime)){
//			delegate();
//			if (!isInterval) {
//				Clear();
//				return true;
//			}
//
//			return true;
//		}
//
//		return false;
//	}
//
//	bool IsSameDelegate(const Delegate& other) const { return other.target<void()>() == delegate.target<void()>(); }
//	
//	size_t GetID() const { return id; }
//
//	bool IsInterval() const { return isInterval; }
//
//	virtual void Clear() {
//		delegate = nullptr;
//	}
//
//rotected:
//	bool isInterval;
//	Delegate delegate;
//	size_t id;
//	Condition condition;
//;

#pragma region Timer
class Timer {
	using Delegate = std::function<void()>;
public:
	Timer()
		: delegate(nullptr), targetTime(0), elapsedTime(0), isInterval(false), id(0) {
	};

	Timer(const Delegate& delegate, float time, bool isInterval, size_t id)
		: targetTime(time), elapsedTime(0), delegate(delegate), isInterval(isInterval), id(id) {
	}

	~Timer() { Clear(); }

	bool UpdateTimer(float deltaTime) {
		if (delegate == nullptr) {
			Clear();
			return true;
		}
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

	bool IsSameDelegate(const Delegate& other) const { return other.target<void()>() == delegate.target<void()>(); }

	size_t GetID() const { return id; }

	bool IsInterval() const { return isInterval; }

	void Clear() {
		delegate = nullptr;
		elapsedTime = 0;
		targetTime = 0;
	}

private:
	float targetTime;
	float elapsedTime;
	bool isInterval;
	Delegate delegate;
	size_t id;
};
#pragma endregion

//#pragma region FrameTimer
//class FrameTimer {
//	using Delegate = std::function<void()>;
//public:
//	FrameTimer()
//		: delegate(nullptr), targetFrame(nullptr), currentFrame(0), isInterval(false), id(0) {
//	};
//
//	FrameTimer(const Delegate& delegate, int& frame, bool isInterval, size_t id)
//		: targetFrame(&frame), currentFrame(0), delegate(delegate), isInterval(isInterval), id(id) {
//	}
//
//	~FrameTimer() { Clear(); }
//
//	bool UpdateTimer(float deltaTime) {
//		++currentFrame;
//		if (*targetFrame >= currentFrame) {
//			delegate();
//			if (!isInterval) {
//				Clear();
//				return true;
//			}
//			currentFrame = 0;
//			return true;
//		}
//
//		return false;
//	}
//
//	bool ReUse(const Delegate& delegate, int& frame, bool isInterval, size_t id) {
//		if (this->delegate) return false;
//		this->isInterval = isInterval;
//		targetFrame = &frame;
//		currentFrame = 0;
//		this->delegate = delegate;
//		return true;
//	}
//
//	bool IsSameDelegate(const Delegate& other) const { return other.target<void()>() == delegate.target<void()>(); }
//
//	size_t GetID() const { return id; }
//
//	bool IsInterval() const { return isInterval; }
//
//	void Clear() {
//		delegate = nullptr;
//		targetFrame = nullptr;
//		currentFrame = 0;
//	}
//
//private:
//	int* targetFrame;
//	int currentFrame;
//	bool isInterval;
//	Delegate delegate;
//	size_t id;
//};
//#pragma endregion