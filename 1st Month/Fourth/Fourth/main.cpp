#include <iostream>'.

#define RTTI(name) \
public: \
	virtual const char* ClassName() const { return #name; }

using namespace std;

class Actor {
	RTTI(Actor)

public:
	virtual void PrintValue() {
		cout << "Value: " << a << '\n';
	}

protected:
	int a = 0;
};

class Player : public Actor {
	RTTI(Player)

public:
	virtual void PrintValue() override {
		cout << "Value: " << b << '\n';
		Actor::PrintValue();
	}

private:
	int b = 15;
};

//다이나믹 캐스트는 어떤 점에서 느린가?
int main() {
	Player* b = new Player();
	Actor* actor = new Actor();

	Actor* a = b;
	
	Player* c = static_cast<Player*>(a);

	Player* p = dynamic_cast<Player*>(actor);

	if (p) {
		p->PrintValue();
	}

	const type_info& info = typeid(a);

	cout << "타입 이름: " << a->ClassName() << '\n';

	cin.get();
	return 0;
}