#pragma once
#include "Solution.h"

class Sol2143 : public Solution {
public:
	virtual void Answer() override;
private:
	int T, n, m;

	int A[1000] = {};
	int B[1000] = {};
	int cumulA[1001] = {};
	int cumulB[1001] = {};
};