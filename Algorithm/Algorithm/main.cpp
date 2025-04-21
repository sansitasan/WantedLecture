#include "PCH.h"
#include "Solution/Sol1976.h"

class _declspec(novtable) ITest {
public:
	virtual void Test() = 0;
	virtual ~ITest() { cout << "delete Itest" << '\n'; }
};

class ProtectedInterface : public ITest {

public:
	virtual void Test() override { cout << "Call protected" << '\n'; }
};



int main() {
	//Solution* s = new Sol1976();
	//
	//s->Answer();

	//class : public I2 {
	//public:
	//	virtual void Test() override { cout << "Test" << '\n'; }
	//	virtual void Test2() override { cout << "Test2" << '\n'; }
	//} obj;
	//
	//obj.Test();
	ITest* t = new ProtectedInterface();
	ProtectedInterface* p = new ProtectedInterface();
	t->Test();
	p->Test();

	cin.get();

	return 0;
}