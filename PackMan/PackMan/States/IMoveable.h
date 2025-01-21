#pragma once
#include <Math/Vector/Vector2.h>

enum class EState {
	Normal,
	Super
};

class IMoveable {
public:
	virtual EState GetState() const = 0;
	virtual Vector2 GetPosition() const = 0;
};