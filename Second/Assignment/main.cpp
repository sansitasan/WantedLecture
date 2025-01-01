#include "Account.h"
#include "Bank.h"

Bank::EAccountType GetAccountType(char input) {
	if (input == 'C' || input == 'c') {
		return Bank::EAccountType::Credit;
	}

	else if (input == 'D' || input == 'd') {
		return Bank::EAccountType::Donation;
	}

	else
		return Bank::EAccountType::Normal;
}

int main() {
	Bank* bank = new Bank();
	char userInput[MAX];
	int id, balance;
	char name[MAX];

	while (true) {
		cout << "\n��ɾ �Է����ּ���.\nC: ���� ����\nD: �Ա�\nW: ���\nI: ��ü �� �ܾ� ��ȸ\nQ: ����\n\n";
		cin >> userInput;
		
		if (userInput[0] == 'Q' || userInput[0] == 'q') break;
		
		else if (userInput[0] == 'C' || userInput[0] == 'c') {
			cout << "���� ������ �����ϼ̽��ϴ�. ���� ������ �Է����ּ���. \n C: �ſ� ����\nD: ��� ����\n N: �Ϲ� ����\n";
			cin >> userInput;

			cout << "\n���¹�ȣ: ";
			cin >> id;
			cout << "\n����: ";
			cin >> name;
			cout << "\n�ܾ�: ";
			cin >> balance;
			cout << "\n\n";

			const Account* account = bank->CreateAccount(id, name, balance, GetAccountType(userInput[0]));

			if (!account) continue;
			account->Inquire();
		}

		else if (userInput[0] == 'D' || userInput[0] == 'd') {
			cout << "�Ա��� �����ϼ̽��ϴ�. �Ա��Ͻ� ���� ������ �Է����ּ���.\n���¹�ȣ: ";
			cin >> id;
			cout << "\n�Ա��Ͻ� �ݾ��� �Է����ּ���.\n�Ա� �ݾ�: ";
			cin >> balance;
			bank->Deposit(id, balance);
		}

		else if (userInput[0] == 'W' || userInput[0] == 'w') {
			cout << "����� �����ϼ̽��ϴ�. ����Ͻ� ���� ������ �Է����ּ���.\n���¹�ȣ: ";
			cin >> id;
			cout << "\n����Ͻ� �ݾ��� �Է����ּ���.\n��� �ݾ�: ";
			cin >> balance;
			bank->Withdraw(id, balance);
		}

		else if (userInput[0] == 'I' || userInput[0] == 'i'){
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