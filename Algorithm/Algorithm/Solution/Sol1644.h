#pragma once
#include "Solution.h"

class Sol1644 : public Solution {
public:
	virtual void Answer() override;

private:
	bool isCNum[4000001];
	vector<int> cumulPrimes;
};