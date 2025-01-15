#include "PCH.h"
#include "Sol2448.h"

void Sol2448::Answer()
{
    Solution::Answer();
	cin >> N;
	memset(pattern, ' ', 3072 * 6144);
    Recursive(N, 0, N - 1);

    for (short i = 0; i < N; ++i) {
        for (short j = 0; j < (N << 1) - 1; ++j) {
            cout << pattern[i][j];
        }
        cout << '\n';
    }
}

void Sol2448::Recursive(short number, short x, short y)
{
    if (number == 3) {
        DrawStar(x, y);
        return;
    }

    short half = number >> 1;

    Recursive(half, x, y);
    Recursive(half, x + half, y - half);
    Recursive(half, x + half, y + half);
}

void Sol2448::DrawStar(short x, short y) {
    pattern[x][y] = '*';
    pattern[x + 1][y - 1] = '*';
    pattern[x + 1][y + 1] = '*';
    for (int i = 0; i < 5; ++i) {
        pattern[x + 2][y - 2 + i] = '*';
    }
}