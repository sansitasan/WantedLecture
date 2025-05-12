#include "PCH.h"
#include "Solution/Sol1976.h"

class _declspec(novtable) ITest {
public:
	virtual void Test() = 0;
	virtual ~ITest() { cout << "delete Itest" << '\n'; }
};

class ProtectedInterface : public ITest {
public:
	ProtectedInterface() { cout << "construct" << '\n'; }
	ProtectedInterface(const ProtectedInterface& x) { cout << "copy" << '\n'; }
	~ProtectedInterface() { cout << "delete" << '\n'; }
	virtual void Test() override { cout << "Call protected" << '\n'; }
};

vector<bool> bit;

void Update(int idx) {
	for (int i = idx + 1; i <= 100001; i += i & -i) {
		bit[i] = bit[i] ^ 1;
	}
}

void RangeUpdate(int start, int end) {
	Update(start);
	Update(end + 1);
}

bool Check(int idx) {
	int ret = 0;
	for (int i = idx + 1; i > 0; i -= i & -i) {
		ret ^= bit[i];
	}

	return ret != 0;
}

vector<vector<int>> operations = {
	{3, 4},
	{2, 3},
	{2, 2}
};

int main() {
	//Solution* s = new Sol1976();
	//
	//s->Answer();
	bit.assign(100001, 0);
	long ans = 0;
	int n = operations.size();
	for (int i = 0; i < n; ++i) {
		RangeUpdate(operations[i][0] - 1, operations[i][1] - 1);
	}

	for (int i = 0; i < n; ++i) {
		if (Check(i)) ans += (i + 1);
	}


	cin.get();

	return 0;
}