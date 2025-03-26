#pragma once
#include "Solution.h"

class Sol2042 : public Solution {
public:
	virtual void Answer() override;
private:
	long long num[1000001] = {};
	long long tree[1000001 << 2] = {};

	void Update(int start, int end, int node, int index, long long value);
	long long Sum(int start, int end, int node, int left, int right);
};