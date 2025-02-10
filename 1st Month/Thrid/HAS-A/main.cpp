#include "Circle.h"


int main() {
	Circle* c = new Circle(3, 5, 2.5f);
	c->ShowData();
	delete c;
	return 0;
}