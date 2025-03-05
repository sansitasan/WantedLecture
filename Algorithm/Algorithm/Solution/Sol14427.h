#pragma once
#include "Solution.h"

//set으로 값을 업데이트 시키는 것보다
//pq로 업데이트되지 않은 값 나중에 버리는 방법이 더 빠르다
class Sol14427 : public Solution {
public:
	virtual void Answer() override;
private:
	int sequence[100001] = {};
	struct Pair {
		Pair(int number, int& value)
			: number(number), value(value) {}
		int number;
		int& value;
	};

	struct Compare {
		bool operator()(const Pair& a, const Pair& b) const {
			if (a.value == b.value) return a.number < b.number;
			return a.value < b.value;
		}
	};
};