#pragma once
#include "Solution.h"

class Sol1766 : public Solution {
public:
	virtual void Answer() override;

private:
	vector<int> graph[32001];
	int counts[32001];
};