#include "PCH.h"
#include "Sol28099.h"

void Sol28099::Answer()
{
	Solution::Answer();

	int T, temp;
	cin >> T;

	for (int i = 0; i < T; ++i) {
		cin >> N;

		for (int j = 1; j <= N; ++j) {
			cin >> temp;
			pq.push(make_pair(temp, j));
		}

		Check();
		memset(tree, 0, (sizeof(int) << 2) * N);
		pq = priority_queue<pair<int, int>, vector<pair<int, int>>, Compare>();
	}
}

void Sol28099::Update(int start, int end, int node, int index)
{
	if (start > index || end < index) return;
	++tree[node];
	if (start == end) return;
	int mid = (start + end) >> 1;
	int next = node << 1;

	Update(start, mid, next, index);
	Update(mid + 1, end, next + 1, index);
}

int Sol28099::Sum(int start, int end, int node, int left, int right)
{
	if (start > right || end < left) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) >> 1;
	int next = node << 1;
	return Sum(start, mid, next, left, right) +
		Sum(mid + 1, end, next + 1, left, right);
}

void Sol28099::Check()
{
	pair<int, int> current;
	int temp, min, max;

	while (!pq.empty()) {
		min = pq.top().second;

		do {
			current = pq.top();
			pq.pop();
			temp = current.first;
			Update(1, N, 1, current.second);
		} while (!pq.empty() && temp == pq.top().first);

		max = current.second;

		if (min == max) continue;

		int temp = Sum(1, N, 1, min, max);
		if (temp - 1 != max - min) {
			cout << "No" << '\n';
			return;
		}
	}

	cout << "Yes" << '\n';
}
