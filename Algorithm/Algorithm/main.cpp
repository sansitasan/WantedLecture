#include "PCH.h"
#include "Solution/Sol1976.h"

class _declspec(novtable) ITest {
public:
	virtual void Test() = 0;
	virtual ~ITest() { cout << "delete Itest" << '\n'; }
};

class ProtectedInterface : public ITest {
public:
	ProtectedInterface() { cout << "construct" << '\n'; }
	ProtectedInterface(const ProtectedInterface& x) { cout << "copy" << '\n'; }
	~ProtectedInterface() { cout << "delete" << '\n'; }
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
	//ITest* t = new ProtectedInterface();
	//ProtectedInterface* p = new ProtectedInterface();
	//t->Test();
	//p->Test();

	//ProtectedInterface x = TestT();

	cin.get();

	return 0;
}