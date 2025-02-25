#include "PCH.h"
#include "Sol9527.h"

void Sol9527::Answer()
{
	Solution::Answer();

	unsigned long long A, B, temp, ans = 0;
	cin >> A >> B;

	for (unsigned long long i = A; i <= B; ++i) {
		temp = i;
		while (temp) {
			ans += temp & 1;
			temp >>= 1;
		}
	}

	cout << ans;
}
