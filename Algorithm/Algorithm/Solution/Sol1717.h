#pragma once
#include "Solution.h"

class Sol1717 : public Solution {
public:
	virtual void Answer() override;

private:
	int uf[1000001] = {};

	int Find(int idx);
	void Check(int idx1, int idx2);
	void Merge(int idx1, int idx2);
};