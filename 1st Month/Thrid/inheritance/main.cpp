#include "Entity/Entity.h"
#include "Entity/Player.h"

//�� void main�� �ȵǴ���?
//���α׷��� ������ ������� ��찡 ������ ��ȯ���� ��� ��
//��� �������� main �ȿ� ������ ���� �ʾƵ� �����Ϸ��� main ���ϰ��� �߰����ְ� ��
//void main�� ���� ������ ��´�

//���� �߰��� ����Ʈ����

//�����͸� ���� ����
//1 ������ ���� ���� �ܿ� �� ������ ����ϱ� ����
//2 �������� ����ϱ� ����

//DI�� ���� - �ұ����̴�
//������ �ش� �ν��Ͻ��� ��� �ϰ�, �̰� �´��� �����ؾ� ��
//Ŀ�ø��� ���� �����̴�

int main() {
	Entity* entity = new Entity();
	Player* player = new Player("Sansei");

	Entity* e2 = player;
	Player* p2 = static_cast<Player*>(e2);

	delete entity;
	delete player;
	return 0;
}