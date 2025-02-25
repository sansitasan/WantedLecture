#pragma once
#include "Solution.h"

class Sol2252 : public Solution {
public:
	virtual void Answer() override;

private:
	int N, M;
	vector<int> graph[32001];
	int counts[32001] = {};
};