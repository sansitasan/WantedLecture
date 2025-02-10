#include <iostream>
#include "Entity/Entity.h"
#include "Entity/Player.h"

using namespace std;

class A {
public:
	void ABC() {}
};

class B {
public:
	void BCD() {}
};

class C : public A, public B {
public:
	void CDE() {}
};

int main() {
	//Player* player = new Player("Sansei");
	//cout << player << '\n';
	//cout << static_cast<IEntity*>(player) << '\n';
	//cout << static_cast<IMovable*>(player) << '\n';

	//virtual�� ���� Ŭ������ ��ӹް�, static_cast�� �غ��� �ּҰ��� ����Ǳ⵵ ��
	C* c = new C();
	B* b = static_cast<B*>(c);
	cout << c << '\n';
	cout << static_cast<A*>(c) << '\n';
	cout << b << '\n';
	//����� ����, virtual�� ������� �ʾƼ� ĳ������ �� ��
	//
	//cout << dynamic_cast<C*>(b) << '\n';


	delete c;

	return 0;
}