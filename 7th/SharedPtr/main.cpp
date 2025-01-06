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

	shared_ptr<Resource> resource = make_shared<Resource>();
	
	{
		shared_ptr<Resource> resource2 = resource;
		cout << "참조 횟수: " << resource.use_count() << '\n';
	}

	cout << "참조 횟수: " << resource.use_count() << '\n';
	//멍청하게 사용하기2
	//unique_ptr<Resource> u(resource.get());
	//cout << "참조 횟수: " << resource.use_count() << '\n';
	return 0;
}