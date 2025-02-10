#include <memory>
#include <iostream>

using namespace std;

class Resource {
public:
	Resource() {
		cout << "생성자 호출!\n";
	}

	~Resource() {
		cout << "소멸자 호출!\n";
	}

	void Use() {
		cout << "자원 사용\n";
	}

	int a = 0;
};

int main() {

	unique_ptr<Resource> resource = make_unique<Resource>();
	//멍청하게 사용하기
	//unique_ptr<Resource> resource2(resource.get());

	resource->Use();
	return 0;
}