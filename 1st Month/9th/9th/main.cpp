#include <iostream>
#include "Stack.h"

int main() {
	Stack<double> stack;
	stack.Push(140.0);

	stack.Push(180.0);

	stack.Push(200.0);

	stack.Push(140.0);

	stack.Push(180.0);

	stack.Push(200.0);

	int count = stack.Size();
	double val;
	while (!stack.Empty()) {
		if (stack.TryPop(val)) {
			std::cout << "value is: " << val << '\n';
		}
	}
	return 0;
}