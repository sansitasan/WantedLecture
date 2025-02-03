#pragma once
#include "Solution.h"

class Sol2206 : public Solution
{
public:
	virtual void Answer() override;

private:
	short dx[4] = { 1, -1, 0, 0 };
	short dy[4] = { 0, 0, 1, -1 };
	short N, M;

	bool visit[1000][1000][2];
	short map[1000][1000];

	int BFS();
};

