#pragma once

#include <vector>
#include "Node.h"

using namespace Quad;

class QuadTree {
public:
	QuadTree(const Bound& bound);
	~QuadTree();

	void Insert(Node* node);

	std::vector<Node*> Query(Node* queryNode);

public:
	//객체 생성 시점과 클래스 생성 시점의 차이로 static은 밖에서 초기화해야 하지만
	//static const만 예외다
	static const int maxDepth = 4;

private:
	Node* root = nullptr;
};