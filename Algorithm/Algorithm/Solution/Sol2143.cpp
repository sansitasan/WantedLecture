#include "PCH.h"
#include "Sol2143.h"

void Sol2143::Answer()
{
	Solution::Answer();
	long long ans = 0;
	cin >> T >> n;
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
		cumulA[i + 1] = cumulA[i] + A[i];
	}

	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> B[i];
		cumulB[i + 1] = cumulB[i] + B[i];
	}

	unordered_map<int, int> subA;
	unordered_map<int, int> subB;

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			++subA[cumulA[j + 1] - cumulA[i]];
		}
	}

	for (int i = 0; i < m; ++i) {
		for (int j = i; j < m; ++j) {
			++subB[cumulB[j + 1] - cumulB[i]];
		}
	}
	unordered_map<int, int>::iterator it;
	for (it = subB.begin(); it != subB.end(); ++it) {
		ans += subA[T - it->first] * (long long)it->second;
	}

	cout << ans;
}
