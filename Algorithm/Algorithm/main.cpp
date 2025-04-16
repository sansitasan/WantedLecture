#include "PCH.h"
#include "Solution/Sol1976.h"

class _declspec(novtable) ITest {
public:
	virtual void Test() = 0;
	virtual ~ITest() { cout << "delete Itest" << '\n'; }
};

class _declspec(novtable) ITest2 {
public:
	virtual void Test2() = 0;
	virtual ~ITest2() { cout << "delete ITest2" << '\n'; }
};

class _declspec(novtable) I2 : public ITest, public ITest2 {

};

class A {
public:
	A() { cout << "def A" << '\n'; }
	~A() { cout << "delete A" << '\n'; }
private:
	int a = 3;
};

class X : public I2 {
public:
	X() { }
	virtual void Test() override { cout << "Test" << '\n'; }
	virtual void Test2() override { cout << "Test2" << '\n'; }
	//~X() override { cout << "delete X" << '\n'; }

private:
	int a = 10;
	A a1;
};

class S
{
public:
	void Func(A* InI)
	{
		std::cout << "ÆãÅ©\n";
		InI = new(&i) A();
	}
public:
	A i;
};

void Test() {
	S stack;
	//X* te = new(&stack) X();
	//delete te;
}

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

	//void* x = malloc(sizeof(X));
	//
	//X* te = new(x) X();
	//
	//delete te;
	Test();

	cin.get();

	return 0;
}