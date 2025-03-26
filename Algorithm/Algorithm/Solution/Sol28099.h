#pragma once
#include "Solution.h"

class Sol28099 : public Solution {
public:
	virtual void Answer() override;

private:
	int tree[200001 << 2] = {};
	int N;

	void Update(int start, int end, int node, int index);
	int Sum(int start, int end, int node, int left, int right);
	void Check();

	struct Compare {
		bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
			if (b.first != a.first) return b.first < a.first;
			return b.second < a.second;
		}
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
};