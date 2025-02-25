#include "PCH.h"
#include "Sol16724.h"

void Sol16724::Answer()
{
	Solution::Answer();
	cin >> N >> M;
	int ans = 1, temp;

	for (int i = 0; i < N; ++i) {
		cin >> map[i];
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (visit[i][j]) continue;
			temp = ans;
			if (DFS(i, j, temp)) {
				++ans;
			}
		}
	}

	cout << ans - 1;
}

bool Sol16724::DFS(int x, int y, int& count)
{
	if (visit[x][y] == count) return true;
	if (visit[x][y]) { 
		count = visit[x][y];
		return false; 
	}

	visit[x][y] = count;
	bool isLoop = false;

	switch (map[x][y])
	{
		case 'L':
			isLoop = DFS(x, y - 1, count);
			break;

		case 'R':
			isLoop = DFS(x, y + 1, count);
			break;

		case 'U':
			isLoop = DFS(x - 1, y, count);
			break;

		case 'D':
			isLoop = DFS(x + 1, y, count);
			break;
	}

	if (!isLoop) visit[x][y] = count;

	return isLoop;
}

void Sol16724::Print()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cout << visit[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << '\n';
}
