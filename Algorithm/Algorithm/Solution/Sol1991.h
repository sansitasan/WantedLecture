#pragma once
#include "Solution.h"

class Sol1991 : public Solution
{
public:
	virtual void Answer() override;

private:
	void PreorderTraversal(const char& node);
	void InorderTraversal(const char& node);
	void PostorderTraversal(const char& node);

private:
	short N;
	char tree[26][2];
};

