#pragma once
#include "Solution.h"

class Sol2473 : public Solution {
public:
	virtual void Answer() override;

private:
	void BinarySearch();

private:
	vector<int> solutions;
};
