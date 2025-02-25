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
	//��ü ���� ������ Ŭ���� ���� ������ ���̷� static�� �ۿ��� �ʱ�ȭ�ؾ� ������
	//static const�� ���ܴ�
	static const int maxDepth = 4;

private:
	Node* root = nullptr;
};