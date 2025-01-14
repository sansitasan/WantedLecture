#include "PCH.h"
#include "Sol1991.h"

void Sol1991::Answer()
{
	Solution::Answer();
	cin >> N;

	char tempParent, tempChild;

	for (char i = 0; i < N; ++i) {
		cin >> tempParent;
		for (char j = 0; j < 2; ++j) {
			cin >> tempChild;
			tree[tempParent - 'A'][j] = tempChild;
		}
	}

	PreorderTraversal('A');
	cout << '\n';
	InorderTraversal('A');
	cout << '\n';
	PostorderTraversal('A');
}

void Sol1991::PreorderTraversal(const char& node)
{
	if (node == '.') return;
	cout << node;
	PreorderTraversal(tree[node - 'A'][0]);
	PreorderTraversal(tree[node - 'A'][1]);
}

void Sol1991::InorderTraversal(const char& node)
{
	if (node == '.') return;
	InorderTraversal(tree[node - 'A'][0]);
	cout << node;
	InorderTraversal(tree[node - 'A'][1]);
}

void Sol1991::PostorderTraversal(const char& node)
{
	if (node == '.') return;
	PostorderTraversal(tree[node - 'A'][0]);
	PostorderTraversal(tree[node - 'A'][1]);
	cout << node;
}
