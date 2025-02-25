#include "PCH.h"
#include "Sol1644.h"

void Sol1644::Answer()
{
	Solution::Answer();
	int N, ans = 0;

	cin >> N;

    isCNum[0] = isCNum[1] = 1;
    cumulPrimes.push_back(0);

    for (int i = 2; i <= N; ++i){
        if (isCNum[i]) continue;
        cumulPrimes.push_back(cumulPrimes.back() + i);

        for (long long j = i * (long long)i; j <= N; j += i) {
            isCNum[j] = true;
        }
    }

    int p1 = 0, p2 = 1;
    int size = cumulPrimes.size();

    while (p1 < size && p2 < size) {
        int temp = cumulPrimes[p2] - cumulPrimes[p1];
        if (temp == N) {
            ++p1;
            ++p2;
            ++ans;
        }
        else if (temp < N) {
            ++p2;
        }

        else {
            ++p1;
        }
    }

	cout << ans;
}
