#pragma once
#include "Solution.h"

class Sol2243 : public Solution {
public:
	virtual void Answer() override;

private:
	void Update(int start, int end, int node, int index, long long value);
	int GetIndex(int start, int end, int node, long long rank);

	long long tree[1000001 << 2] = {};
};