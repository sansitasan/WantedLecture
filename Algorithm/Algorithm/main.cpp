#include "PCH.h"
#include <string>
#include "Solution/Sol14427.h"
#include <chrono>

int x = 2;

class A {
public:
	virtual void CoutX(int x = 10) {
		cout << x;
	}

protected:
	float x = 1.5f;
};

class B : public A {
public:
	virtual void CoutX() {
		cout << x;
	}

	void Coutx(int x = 7) {
		cout << x;
	}

private:
	char x = '3';
};

int main() {
	//Solution* s = new Sol14427();
	//
	//s->Answer();
	B* b = new B();
	b->CoutX(10);

	delete b;

	return 0;
}