#include "PCH.h"
#include "Sol2206.h"

void Sol2206::Answer()
{
	Solution::Answer();
	cin >> N >> M;
	string temp;

	for (short i = 0; i < N; ++i) {
		cin >> temp;
		for (short j = 0; j < M; ++j) {
			map[i][j] = temp[j] - '0';
		}
	}

	cout << BFS();
}

int Sol2206::BFS()
{
	queue<tuple<short, short, bool>> q;
	q.push({ 0, 0, false });
	visit[0][0][0] = true;
	int count = 1, size;
	short nx, ny;

	while (!q.empty()) {
		size = q.size();
		while (size--) {
			auto [x, y, isBreak] = q.front();

			q.pop();

			if (x == N - 1 && y == M - 1) return count;

			for (short i = 0; i < 4; ++i) {
				nx = x + dx[i];
				ny = y + dy[i];
				
				if (nx < 0 || nx > N - 1 || ny < 0 || ny > M - 1) continue;
				
				if (!map[nx][ny] && !visit[nx][ny][isBreak]) {
					visit[nx][ny][isBreak] = true;
					q.push({ nx, ny, isBreak });
				}

				if (map[nx][ny] && !isBreak && !visit[nx][ny][1]) {
					visit[nx][ny][1] = true;
					q.push({ nx, ny, true });
				}
			}
		}

		++count;
	}
	return -1;
}
