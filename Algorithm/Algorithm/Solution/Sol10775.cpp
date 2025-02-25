#include "PCH.h"
#include "Sol10775.h"

void Sol10775::Answer()
{
	Solution::Answer();
	int gi;
	bool canDock;
	cin >> G >> P;
	int ans = 0;
	//int testArr[] = { 15, 14, 13, 12, 11, 10, 9, 15, 15, 15, 15, 15, 15, 6, 1, 16, 17, 15, 15, 15 };

	for (int i = 0; i < P; ++i) {
		cin >> gi;
		//gi = testArr[i];

		canDock = Find(1, G, 1, gi);

		if (!canDock) break;

		//Update(1, G, 1, gi);
		++ans;
	}

	cout << ans;
}

int Sol10775::Sum(int start, int end, int node, int left, int right)
{
	if (left > end || right < start) return 0;

	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) >> 1;
	return Sum(start, mid, node << 1, left, right) + 
		Sum(mid + 1, end, (node << 1) + 1, left, right);
}

void Sol10775::Update(int start, int end, int node, int index)
{
	if (index < start || index > end) return;
	++tree[node];
	if (start == end) return;
	int mid = (start + end) >> 1;
	Update(start, mid, node << 1, index);
	Update(mid + 1, end, (node << 1) + 1, index);
}

bool Sol10775::Find(int start, int end, int node, int value)
{
	if (start > value) return false;
	if (tree[node] > end - start) return false;

	if (start == end) {
		++tree[node];
		return !(tree[node] - 1);
	}
	int mid = (start + end) >> 1;

	if (Find(mid + 1, end, (node << 1) + 1, value)) {
		++tree[node];
		return true;
	}

	if (Find(start, mid, node << 1, value)) {
		++tree[node];
		return true;
	}

	return false;
}
