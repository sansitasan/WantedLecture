#include "PCH.h"
#include "Sol14427.h"

void Sol14427::Answer()
{
	Solution::Answer();
	set<Pair, Compare> seq;
	int N, M, temp;
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> sequence[i];
		seq.insert(Pair(i, sequence[i]));
	}

	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> temp;
		if (temp == 1) {
			int num, val;
			cin >> num >> val;
			seq.erase(seq.find(Pair(num, sequence[num])));
			sequence[num] = val;
			seq.insert(Pair(num, sequence[num]));
			continue;
		}

		cout << (*seq.begin()).number << '\n';
	}
}
