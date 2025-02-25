#include "PCH.h"
#include "Sol1766.h"

void Sol1766::Answer()
{
	Solution::Answer();
	int N, M, A, B;
	cin >> N >> M;
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < M; ++i) {
		cin >> A >> B;
		graph[A].push_back(B);
		++counts[B];
	}

	for (int i = 1; i <= N; ++i) {
		if (counts[i]) continue;
		pq.push(i);
	}

	while (!pq.empty()) {
		A = pq.top();
		pq.pop();

		for (int i = 0; i < graph[A].size(); ++i) {
			if (--counts[graph[A][i]]) continue;
			pq.push(graph[A][i]);
		}


		cout << A << ' ';
	}
}