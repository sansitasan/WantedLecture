#pragma once
#include "Solution.h"

class Sol1976 : public Solution {
public:
	virtual void Answer() override;

private:
	void Merge(short a, short b);
	int Find(short a);

private:
	short uf[201] = {};
};