#include "PCH.h"
#include "Sol1976.h"

void Sol1976::Answer()
{
	Solution::Answer();
	short N, M, travel, root;
	bool temp;
	cin >> N >> M;

	for (short i = 1; i <= N; ++i) {
		uf[i] = i;
	}

	for (short i = 1; i <= N; ++i) {
		for (short j = 1; j <= N; ++j) {
			cin >> temp;
			if (temp) Merge(i, j);
		}
	}

	cin >> travel;
	root = Find(travel);

	for (int i = 1; i < M; ++i) {
		cin >> travel;
		if (root != Find(travel)) {
			cout << "NO";
			return;
		}
	}
	cout << "YES";
}

void Sol1976::Merge(short a, short b)
{
	if (uf[a] == uf[b]) return;

	int aroot = Find(a);
	int broot = Find(b);

	uf[aroot] = broot;
}

int Sol1976::Find(short a)
{
	if (uf[a] == a) return a;
	return uf[a] = Find(uf[a]);
}
