#include "Vector2.h"

//std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
//	os << "(" << vector.GetX() << ", " << vector.GetY() << ")\n";
//	return os;
//}

int main() {
	Vector2 pos(4, 4);
	Vector2 speed(.5f, .5f);

	std::cout << pos;
	return 0;
}