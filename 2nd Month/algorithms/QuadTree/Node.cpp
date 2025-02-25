#include "Node.h"
#include "QuadTree.h"

namespace Quad {
	Node::Node(const Bound& bound, int depth)
		: bound(bound), depth(depth)
	{

	}

	Node::~Node() {
		Clear();
	}

	void Node::Insert(Node* node)
	{
		ENodeIndex result = TestRegion(node->GetBound());
		if (result == ENodeIndex::Straddling) {
			points.emplace_back(node);
		}

		else if (result != ENodeIndex::OutOfArea) {
			if (SubDivide()) child[(int)result]->Insert(node);
			else points.emplace_back(node);
		}
	}

	void Node::Query(const Bound& queryBounds, std::vector<Node*>& possibleNodes)
	{
		possibleNodes.emplace_back(this);
		if (IsDivided()) {
			std::vector<ENodeIndex> quads = GetQuads(queryBounds);

			for (ENodeIndex& index : quads) {
				child[(int)index]->Query(queryBounds, possibleNodes);
			}
		}
	}

	void Node::Clear()
	{
		for (Node* node : points) {
			SafeDelete(node);
		}

		points.clear();

		if (IsDivided()) {
			for (int i = 0; i < (int)EDir::Size; ++i) {
				child[i]->Clear();
			}

			ClearChildren();
		}
	}

	inline bool Node::SubDivide()
	{
		if (depth == QuadTree::maxDepth) return false;
		
		if (!IsDivided()) {
			int x = bound.X();
			int y = bound.Y();
			int halfWidth = bound.Width() >> 1;
			int halfHeight = bound.Height() >> 1;

			child[(int)EDir::TopLeft] = new Node(Bound(x, y, halfWidth, halfHeight), depth + 1);
			child[(int)EDir::TopRight] = new Node(Bound(x + halfWidth, y, halfWidth, halfHeight), depth + 1);
			child[(int)EDir::BottomLeft] = new Node(Bound(x, y, halfWidth, halfHeight), depth + 1);
			child[(int)EDir::BottomRight] = new Node(Bound(x + halfWidth, y + halfHeight, halfWidth, halfHeight), depth + 1);
		}
		return true;
	}

	inline bool Node::IsDivided()
	{
		return child[(int)EDir::TopLeft] != nullptr;
	}

	inline void Node::ClearChildren()
	{
		if (IsDivided()) {
			for (int i = 0; i < (int)EDir::Size; ++i) {
				SafeDelete(child[i]);
			}
		}
	}

	inline ENodeIndex Node::TestRegion(const Bound& bound)
	{
		std::vector<ENodeIndex> quads = GetQuads(bound);

		if (!quads.size()) return ENodeIndex::OutOfArea;
		if (quads.size() == 1) return quads[0];

		return ENodeIndex::Straddling;
	}

	inline std::vector<ENodeIndex> Node::GetQuads(const Bound& bound)
	{
		std::vector<ENodeIndex> quads;

		//영역 계산에 필요한 변수
		int x = this->bound.X();
		int y = this->bound.Y();
		int halfWidth = this->bound.Width() >> 1;
		int halfHeight = this->bound.Height() >> 1;
		int centerX = x + halfWidth;
		int centerY = y + halfHeight;
		
		//영역 확인
		bool left = bound.X() < centerX && bound.MaxX() >= x;
		bool right = bound.MaxX() >= centerX && bound.X() < this->bound.MaxX();

		bool top = bound.Y() < centerY && bound.MaxY() >= y;
		bool bottom = bound.MaxY() >= centerY && bound.Y() < this->bound.MaxY();

		if (top && left) {
			quads.emplace_back(ENodeIndex::TopLeft);
		}
		if (top && right) {
			quads.emplace_back(ENodeIndex::TopRight);
		}
		if (bottom && left) {
			quads.emplace_back(ENodeIndex::BottomLeft);
		}
		if (bottom && right) {
			quads.emplace_back(ENodeIndex::BottmRight);
		}

		return quads;
	}
}