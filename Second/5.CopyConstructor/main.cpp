#include <iostream>

class Player {
public:
	Player()
	: x(0), y(0){
		size_t length = strlen("Player") + 1;
		name = new char[length];

		strcpy_s(name, length, "Player");

		//위와 같음
		//memcpy(name, "Player", length - 1);
		//name[length - 1] = '\0';
		std::cout << "Player() called\n";
	}

	Player(const char* name, int x, int y) 
		: x(x), y(y) {
		size_t length = strlen(name) + 1;
		this->name = new char[length];
		strcpy_s(this->name, length, name);

		std::cout << "Player(int number) called\n";
	}

	Player(const Player& other)
		: x(other.x), y(other.y) {

		size_t length = strlen(other.name) + 1;
		this->name = new char[length];
		strcpy_s(this->name, length, other.name);
		std::cout << "Player(const Player& other) called\n";
	}

	void Print() {
		std::cout << "name: " << name << "x: " << x << ", y: " << y << '\n';
	}

	~Player() {
		delete[] name;
	}

private:
	int x;
	int y;
	char* name;
};

int main() {
	Player p2 = Player("Player2", 10, 12);
	Player p3 = Player(p2);

	p2.Print();
	p3.Print();
	std::cin.get();
	return 0;
}