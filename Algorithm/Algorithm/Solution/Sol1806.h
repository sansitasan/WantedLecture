#pragma once
#include "Solution.h"

class Sol1806 : public Solution
{
public:
	virtual void Answer() override;

private:
	int N, S, cumul = 0, ans = 0;

	int seq[100001];
};