#include "Account.h"

int main() {
	Bank* bank = new Bank();
	char input[MAX];
	int id, balance;
	char name[MAX];

	while (true) {
		cout << "\n��ɾ �Է����ּ���.\nC: ���� ����\nD: �Ա�\nW: ���\nI: ��ü �� �ܾ� ��ȸ\nQ: ����\n\n";
		cin >> input;
		
		if (input[0] == 'Q' || input[0] == 'q') break;
		
		else if (input[0] == 'C' || input[0] == 'c') {
			cout << "���� ������ �����ϼ̽��ϴ�. ���� ������ �Է����ּ���. \n���¹�ȣ: ";
			cin >> id;
			cout << "\n����: ";
			cin >> name;
			cout << "\n�ܾ�: ";
			cin >> balance;
			cout << "\n\n";
			bank->CreateAccount(id, name, balance);
			cout << "���¹�ȣ: " << id << " ����: " << name << " �ܾ�: " << balance << " ���� ���� ������ �Ϸ��߽��ϴ�.\n";
		}

		else if (input[0] == 'D' || input[0] == 'd') {
			cout << "�Ա��� �����ϼ̽��ϴ�. �Ա��Ͻ� ���� ������ �Է����ּ���.\n���¹�ȣ: ";
			cin >> id;
			cout << "\n�Ա��Ͻ� �ݾ��� �Է����ּ���.\n�Ա� �ݾ�: ";
			cin >> balance;
			bank->Deposit(id, balance);
		}

		else if (input[0] == 'W' || input[0] == 'w') {
			cout << "����� �����ϼ̽��ϴ�. ����Ͻ� ���� ������ �Է����ּ���.\n���¹�ȣ: ";
			cin >> id;
			cout << "\n����Ͻ� �ݾ��� �Է����ּ���.\n��� �ݾ�: ";
			cin >> balance;
			bank->Withdraw(id, balance);
		}

		else if (input[0] == 'I' || input[0] == 'i'){
			cout << "��ü �� �ܾ� ��ȸ�� �����ϼ̽��ϴ�.\n";
			bank->Inquire();
		}

		else {
			cout << "�ùٸ� ��ɾ �Է����ּ���.\n";
		}

	}

	cout << "���α׷��� �����մϴ�.\n";
	delete bank;
	return 0;
}