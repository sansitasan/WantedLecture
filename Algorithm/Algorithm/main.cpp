#include "PCH.h"
#include "Solution/Sol1976.h"

class Test {
public:
	Test() = delete;
	Test(int xx)
		: x(xx) {}

	~Test() {
		cout << x << '\n';
	}

	void T() { cout << x << '\n'; }
	int x;
};

void TTT() {
	void* t = malloc(sizeof(Test));
	Test* tt = static_cast<Test*>(t);

	free(t);
}

int main() {
	//Solution* s = new Sol1976();
	//
	//s->Answer();
	//::new (static_cast<void*>(_STD addressof(_Obj))) Test;
	//std::addressof<Test>();
	TTT();
	vector<Test> x;
	x.push_back(Test(1));

	//Test* pc = nullptr;
	//
	//Test& rc = *pc;

	cin.get();

	return 0;
}