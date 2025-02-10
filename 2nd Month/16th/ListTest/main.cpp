#include <iostream>
#include <list>

using namespace std;

struct Pos {
	Pos(char name, int x, int y)
		: name(name), x(x), y(y) {
	}

	char name;
	int x;
	int y;
};

ostream& operator<<(ostream& os, const Pos& pos) {
	return os << pos.name << " X: " << pos.x << ", Y: " << pos.y;
}

int main() {
	list<Pos> poses;
	poses.push_back(Pos('A', 50, 200));
	poses.push_back(Pos('B', 20, 80));
	poses.push_back(Pos('C', 75, 10));
	poses.push_back(Pos('D', 130, 80));
	poses.push_back(Pos('E', 100, 200));

	list<Pos>::iterator e, c;
	for (auto it = poses.begin(); it != poses.end(); ++it) {
		cout << *it << '\n';
		if ((*it).name == 'E') e = it;
	}

	cout << '\n';
	poses.insert(e, Pos('F', 300, 300));

	for (auto it = poses.begin(); it != poses.end(); ++it) {
		if ((*it).name == 'D') {
			(*it).x = 200;
			(*it).y = 100;
		}
		else if ((*it).name == 'C') {
			c = it;
		}

		cout << *it << '\n';
	}

	cout << '\n';
	poses.erase(c);

	for (auto it = poses.begin(); it != poses.end(); ++it) {
		cout << *it << '\n';
	}

	return 0;
}