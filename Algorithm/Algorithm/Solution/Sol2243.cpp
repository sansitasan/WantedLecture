#include "PCH.h"
#include "Sol2243.h"

#define Max 1000000

void Sol2243::Answer()
{
    Solution::Answer();
    int N;
    int a;
    long long b, c;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> a >> b;
        if (a == 1) {
            int temp = GetIndex(1, Max, 1, b);
            cout << temp << '\n';
            Update(1, Max, 1, temp, -1);
            continue;
        }

        cin >> c;
        Update(1, Max, 1, b, c);
    }
}

void Sol2243::Update(int start, int end, int node, int index, long long value)
{
    if (start > index || end < index) return;
    tree[node] += value;
    if (start == end) return;
    int mid = (start + end) >> 1;
    int next = node << 1;
    Update(start, mid, next, index, value);
    Update(mid + 1, end, next + 1, index, value);
}

int Sol2243::GetIndex(int start, int end, int node, long long rank)
{
    if (tree[node] < rank || !tree[node]) return -1;
    if (start == end) return end;
    int mid = (start + end) >> 1;
    int next = node << 1;

    int value = GetIndex(start, mid, next, rank);
    if (value != -1) return value;

    value = GetIndex(mid + 1, end, next + 1, rank - tree[next]);

    return value;
}
