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

	//virtual이 없는 클래스를 상속받고, static_cast를 해보면 주소값이 변경되기도 함
	C* c = new C();
	B* b = static_cast<B*>(c);
	cout << c << '\n';
	cout << static_cast<A*>(c) << '\n';
	cout << b << '\n';
	//여기는 에러, virtual이 선언되지 않아서 캐스팅이 안 됨
	//
	//cout << dynamic_cast<C*>(b) << '\n';


	delete c;

	return 0;
}