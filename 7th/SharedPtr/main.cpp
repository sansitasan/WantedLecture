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

	shared_ptr<Resource> resource = make_shared<Resource>();
	
	{
		shared_ptr<Resource> resource2 = resource;
		cout << "���� Ƚ��: " << resource.use_count() << '\n';
	}

	cout << "���� Ƚ��: " << resource.use_count() << '\n';
	//��û�ϰ� ����ϱ�2
	//unique_ptr<Resource> u(resource.get());
	//cout << "���� Ƚ��: " << resource.use_count() << '\n';
	return 0;
}