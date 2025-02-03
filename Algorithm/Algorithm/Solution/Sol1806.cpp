#include "PCH.h"
#include "Sol1806.h"

void Sol1806::Answer()
{
	Solution::Answer();
	cin >> N >> S;
	int p1 = 0, p2 = 0;

	for (int i = 0; i < N; ++i) {
		cin >> seq[i];
		cumul += seq[i];
		++p2;
		if (cumul < S) continue;

		while (cumul >= S) {
			cumul -= seq[p1++];
		}

		cumul += seq[--p1];

		if (!ans) ans = p2 - p1;
		
		else {
			ans = ans < p2 - p1 ? ans : p2 - p1;
		}

		if (ans == 1) break;
	}

	cout << ans;
}
