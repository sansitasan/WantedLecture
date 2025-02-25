#include "PCH.h"
#include "Sol9466.h"

void Sol9466::Answer()
{
	Solution::Answer();
	int T, n, ans;

	cin >> T;

	for (int i = 0; i < T; ++i) {
		cin >> n;
		ans = 0;
		for (int j = 1; j <= n; ++j) {
			cin >> students[j][0];
		}

		for (int j = 1; j <= n; ++j) {
			DFS(j, j);
			if (students[j][1] == -1) ++ans;
		}


		cout << ans << '\n';
		memset(students + 1, 0, (sizeof(int) << 1) * n);
	}
}

int Sol9466::DFS(int idx, int set)
{
	if (students[idx][1]) return -1;
	if (!students[idx][1]) students[idx][1] = set;

	if (students[idx][0] == idx) {
		return -1;
	}

	if (students[students[idx][0]][1] == set) {

		return students[idx][0];
	}

	int val = DFS(students[idx][0], set);
	if (val == -1) students[idx][1] = -1;
	if (val == idx) val = -1;
	return val;
}
