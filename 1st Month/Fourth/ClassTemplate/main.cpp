#include <iostream>

using namespace std;

template<typename T>
class Data {
public:
	Data(T newData) : data(newData) {

	}

	T GetData() const { return data; }

	void SetData(T newData) {
		data = newData;
	}

private:
	T data;
};

int main() {

	Data<int> data(10);
	Data<float> pi(3.141592f);

	cin.get();
	return 0;
}