#include "Entity/Entity.h"
#include "Entity/Player.h"

//왜 void main은 안되는지?
//프로그램이 비정상 종료됐을 경우가 있으니 반환값을 줘야 함
//어느 순간부터 main 안에 리턴을 쓰지 않아도 컴파일러가 main 리턴값을 추가해주게 됨
//void main은 이제 오류를 뱉는다

//필터 추가는 소프트폴더

//포인터를 쓰는 이유
//1 정적인 스택 공간 외에 힙 공간을 사용하기 위해
//2 다형성을 사용하기 위해

//DI의 단점 - 소극적이다
//누군가 해당 인스턴스를 줘야 하고, 이게 맞는지 검증해야 함
//커플링을 끊는 패턴이다

int main() {
	Entity* entity = new Entity();
	Player* player = new Player("Sansei");

	Entity* e2 = player;
	Player* p2 = static_cast<Player*>(e2);

	delete entity;
	delete player;
	return 0;
}