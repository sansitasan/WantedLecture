#pragma once
#include "Solution.h"

class Sol2448 : public Solution
{
public:
	virtual void Answer() override;

private:
	void Recursive(short num, short x, short y);
	void DrawStar(short x, short y);
	short N;
	char pattern[3072][6144];
};

