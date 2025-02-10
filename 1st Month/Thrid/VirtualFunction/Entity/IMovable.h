#pragma once

class IMovable {
public:
	virtual void Move(int xAmount, int yAmount) = 0;
};