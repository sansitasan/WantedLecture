#include <memory>
#include <iostream>

using namespace std;

class Resource {
public:
	Resource() {
		cout << "������ ȣ��!\n";
	}

	~Resource() {
		cout << "�Ҹ��� ȣ��!\n";
	}

	void Use() {
		cout << "�ڿ� ���\n";
	}

	int a = 0;
};

int main() {

	unique_ptr<Resource> resource = make_unique<Resource>();
	//��û�ϰ� ����ϱ�
	//unique_ptr<Resource> resource2(resource.get());

	resource->Use();
	return 0;
}