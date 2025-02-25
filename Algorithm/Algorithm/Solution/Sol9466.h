#pragma once
#include "Solution.h"

class Sol9466 : public Solution {
public:
	virtual void Answer() override;

private:
	int DFS(int idx, int set);
	int students[100001][2] = {};
};