#pragma once
#include "Bound.h"
#include <vector>

namespace Quad {
	template<typename T>
	void SafeDelete(T*& t) {
		if (t) {
			delete t;
			t = nullptr;
		}
	}

	enum class ENodeIndex {
		TopLeft,	//������ ���Ե� ��
		TopRight,
		BottomLeft,
		BottmRight,
		Straddling,	//��輱�� ��ģ ��
		OutOfArea	//������ ��� ��
	};

	enum class EDir {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Size
	};

	class Node {
	public:
		Node(const Bound& bound, int depth = 0);
		~Node();

		void Insert(Node* node);

		void Query(const Bound& queryBounds, std::vector<Node*>& possibleNodes);

		void Clear();

		inline Bound GetBound() const { return bound; }

		inline const std::vector<Node*>& Points() const { return points; }

		inline Node* Child(EDir dir) const { return child[(int)dir]; }

		inline int Depth() const { return depth; }

	private:
		//���� ���ҽ� ���
		inline bool SubDivide();

		//���� ���� Ȯ��
		inline bool IsDivided();

		inline void ClearChildren();

		//������ ������ ��ġ�� ������ ��ȯ
		inline ENodeIndex TestRegion(const Bound& bound);

		//������ ������ ���Եǰų� ��ġ�� ������ ��� ���ϴ� �Լ�
		inline std::vector<ENodeIndex> GetQuads(const Bound& bound);

	private:
		//���� ����� ����
		int depth = 0;
		//���� ����
		Bound bound;

		std::vector<Node*> points;

		Node* child[4] = {};
	};
}