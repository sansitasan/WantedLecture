#pragma once
#include "Solution.h"

class Sol16724 : public Solution {
public:
	virtual void Answer() override;

private:
	bool DFS(int x, int y, int& count);
	void Print();
	int N, M;
	string map[1000] = {};
	int visit[1000][1000] = {};
};