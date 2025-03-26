#include "PCH.h"
#include "Sol2042.h"

void Sol2042::Answer()
{
	Solution::Answer();
	int N, M, K;
	long long a, b, c, temp;

	cin >> N >> M >> K;
	M += K;

	for (int i = 1; i <= N; ++i) {
		cin >> temp;
		Update(1, N, 1, i, temp);
		num[i] = temp;
	}

	for (int i = 0; i < M; ++i) {
		cin >> a >> b >> c;
		if (a == 1) {
			Update(1, N, 1, b, c);
			num[b] = c;
			continue;
		}

		temp = Sum(1, N, 1, b, c);
		cout << temp << '\n';
	}
}

void Sol2042::Update(int start, int end, int node, int index, long long value)
{
	if (index < start || end < index) return;

	tree[node] += (value - num[index]);
	if (start == end) return;
	int mid = (start + end) >> 1;
	int next = node << 1;
	Update(start, mid, next, index, value);
	Update(mid + 1, end, next + 1, index, value);
}

long long Sol2042::Sum(int start, int end, int node, int left, int right)
{
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) >> 1;
	int next = node << 1;
	return Sum(start, mid, next, left, right) + Sum(mid + 1, end, next + 1, left, right);
}
