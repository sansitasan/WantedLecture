#pragma once
#include "Solution.h"

class Sol10775 : public Solution {
public:
	virtual void Answer() override;

private:
	int Sum(int start, int end, int node, int left, int right);
	void Update(int start, int end, int node, int index);
	bool Find(int start, int end, int node, int value);
	int G, P;
	int counts[100001] = {};
	int tree[100001 << 2] = {};
};