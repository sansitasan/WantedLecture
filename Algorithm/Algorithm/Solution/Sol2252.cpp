#include "PCH.h"
#include "Sol2252.h"

void Sol2252::Answer()
{
	Solution::Answer();

	cin >> N >> M;
	int A, B;
	queue<int> q;

	for (int i = 0; i < M; ++i) {
		cin >> A >> B;
		graph[A].push_back(B);
		++counts[B];
	}

	for (int i = 1; i <= N; ++i) {
		if (counts[i]) continue;
		q.push(i);
	}

 	while (!q.empty()) {
		A = q.front();
		q.pop();

		for (int i = 0; i < graph[A].size(); ++i) {
			if (--counts[graph[A][i]] > 0) continue;
			q.push(graph[A][i]);
		}

		cout << A << ' ';
	}
}
