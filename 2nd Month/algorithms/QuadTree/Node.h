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
		TopLeft,	//영역에 포함된 것
		TopRight,
		BottomLeft,
		BottmRight,
		Straddling,	//경계선에 걸친 것
		OutOfArea	//영역을 벗어난 것
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
		//영역 분할시 사용
		inline bool SubDivide();

		//영역 분할 확인
		inline bool IsDivided();

		inline void ClearChildren();

		//전달한 영역과 겹치는 영역을 반환
		inline ENodeIndex TestRegion(const Bound& bound);

		//전달한 영역이 포함되거나 걸치는 영역을 모두 구하는 함수
		inline std::vector<ENodeIndex> GetQuads(const Bound& bound);

	private:
		//현재 노드의 깊이
		int depth = 0;
		//현재 영역
		Bound bound;

		std::vector<Node*> points;

		Node* child[4] = {};
	};
}