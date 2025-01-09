#include "PCH.h"
#include "2473.h"

void Sol2473::BinarySearch() {

}

void Sol2473::Answer() {
	Solution::Answer();
	int N;
	cin >> N;

	solutions.assign(N, 0);

	for (int i = 0; i < N; ++i) {
		cin >> solutions[i];
	}

	sort(solutions.begin(), solutions.end());

	int answer[3] = { solutions[0], solutions [1], solutions [2] }, left = 0, right;
	long long  fixed, temp1, temp2, minimum = 20000000000;
	bool flag = false;
	
	for (int i = 0; i < N - 2; ++i) {
		fixed = solutions[i];
		left = i + 1;
		right = N - 1;
		
		while (left < right) {
			temp1 = fixed + solutions[left] + solutions[right];
			temp2 = abs(temp1);
			if (minimum > temp2) {
				minimum = temp2;
				answer[0] = fixed;
				answer[1] = solutions[left];
				answer[2] = solutions[right];
			}

			if (temp1 > 0) {
				--right;
			}

			else if (temp1 < 0) {
				++left;
			}

			else {
				flag = true;
				break;
			}
		}

		if (flag) break;
	}

	for (int i = 0; i < 3; ++i) {
		cout << answer[i] << ' ';
	}
}