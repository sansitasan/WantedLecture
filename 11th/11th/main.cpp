#include <iostream>
#include "Queue.h"

using namespace std;

int main() {
	Queue<int> q;
	q.Enqueue(10);
	q.Enqueue(20);
	q.Enqueue(30);
	q.Enqueue(40);
	q.Enqueue(50);
	q.Enqueue(60);
	q.Enqueue(70);
	q.Enqueue(80);
	q.Enqueue(90);
	q.Enqueue(100);
	q.Enqueue(110);

	q.Display();

	int val = 0;
	if (q.Dequeue(val)) {
		cout << "값은 " << val << "입니다.\n";
	}

	if (q.Dequeue(val)) {
		cout << "값은 " << val << "입니다.\n";
	}

	if (q.Dequeue(val)) {
		cout << "값은 " << val << "입니다.\n";
	}

	if (q.Dequeue(val)) {
		cout << "값은 " << val << "입니다.\n";
	}
	q.Display();

	return 0;
}