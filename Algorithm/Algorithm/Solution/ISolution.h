#pragma once

class ISolution {
public:
	ISolution() = default;
	virtual ~ISolution() = default;
	virtual void Answer() = 0;

protected:
};
