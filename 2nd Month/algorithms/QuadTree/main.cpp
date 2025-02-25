#include <iostream>
#include "QuadTree.h"

int main() {
	QuadTree tree(Bound(0, 0, 200, 200));

	tree.Insert(new Node(Bound(50, 50)));
	tree.Insert(new Node(Bound(60, 80)));
	tree.Insert(new Node(Bound(90, 120)));
	tree.Insert(new Node(Bound(150, 150)));
	tree.Insert(new Node(Bound(10, 10)));

	std::cout << "노드 삽입 완료.\n";

	Node testNode(Bound(45, 45, 40, 40));
	std::vector<Node*> intersects = tree.Query(&testNode);

	if (intersects.empty()) {
		std::cout << "겹치는 노드 없음\n";
	}

	else {
		std::cout << "겹치는 노드를 " << intersects.size() << "개 찾음\n";
	}
}