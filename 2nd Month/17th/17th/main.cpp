#include "Sort.h"

class X {
public:
	int c = 10;
private:

};

class Test {
public:
	Test() { A(); a = new X(); }
	virtual ~Test() {}
	virtual void A() { cout << "A\n"; }
	virtual void B() {}
	void C() const {
		a->c = 12;
	}
private:
	char x;
	X* a;
};

class Test1 : public Test {
public:
	Test1() {}
	virtual void A() override { cout << "B\n"; }
	virtual void B() override { A(); }
};

int main() {
	
	int arr[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25 };
	int len = _countof(arr);
	
	cout << "정렬 전: ";
	ISort* sort = new HeapSort();
	
	sort->Print(arr, len);
	
	sort->Sort(arr, len - 1);
	
	cout << "정렬 후: ";
	sort->Print(arr, len);
	

	cin.get();
	return 0;
}