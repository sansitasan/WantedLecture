#pragma once
#include "Solution.h"

//set���� ���� ������Ʈ ��Ű�� �ͺ���
//pq�� ������Ʈ���� ���� �� ���߿� ������ ����� �� ������
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