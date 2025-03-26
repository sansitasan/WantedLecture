#include "PCH.h"
#include "Sol1717.h"

void Sol1717::Answer()
{
	Solution::Answer();
	int n, m;
	cin >> n >> m;
	int oper, a, b;

	for (int i = 1; i <= n; ++i) {
		uf[i] = i;
	}

	for (int i = 0; i < m; ++i) {
		cin >> oper >> a >> b;

		if (oper) {
			Check(a, b);
			continue;
		}

		Merge(a, b);
	}
}

int Sol1717::Find(int idx)
{
	if (idx == uf[idx]) return idx;
	return uf[idx] = Find(uf[idx]);
}

void Sol1717::Check(int idx1, int idx2)
{
	idx1 = Find(idx1);
	idx2 = Find(idx2);
	if (idx1 == idx2) {
		cout << "YES" << '\n';
		return;
	}

	cout << "NO" << '\n';
}

void Sol1717::Merge(int idx1, int idx2)
{
	idx1 = Find(idx1);
	idx2 = Find(idx2);
	uf[idx1] = idx2;
}
