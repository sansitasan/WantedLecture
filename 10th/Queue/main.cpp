#include "Queue.h"

int main() {
	Queue<int> q;
	for (int i = 0; i < 5; ++i) {
		q.Enqueue(i);
	}

	cout << q.Dequeue() << '\n';
	cout << q.Dequeue() << '\n';
	cout << q.Dequeue() << '\n';

	for (int i = 0; i < 5; ++i) {
		q.Enqueue(i);
	}

	while (!q.Empty()) {
		cout << q.Dequeue() << '\n';
	}
	return 0;
 }