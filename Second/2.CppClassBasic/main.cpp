#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#else
#define new new
#endif

class Player {
public:
	Player()
		: x(0), y(0), speed(1) {
		std::cout << "생성자 호출\n";
	}

	Player(int x, int y, int speed)
		: x(x), y(y), speed(speed) {
		std::cout << "생성자 호출\n";
	}

	~Player() {
		std::cout << "소멸자 호출\n";
	}

	void Move(int x, int y) {
		this->x += x;
		this->y += y;
	}

protected:

private:
	int x;
	int y;
	int speed;
};

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetDbgFlag로 잡은 수를 여기 넣어주면 실행 시 위치를 알려줌
	//_CrtSetBreakAlloc(158);

	Player p;
	p.Move(10, 20);
	Player* p1 = new Player();
	delete p1;
	p1 = nullptr;

	std::cin.get();
	return 0;
}