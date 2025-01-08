#pragma once
#include "ISolution.h"

class Sol2473 : public ISolution {
public:
	virtual void Answer() override;

private:
	void BinarySearch();

private:
	vector<int> solutions;
};
