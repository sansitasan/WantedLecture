#include "Account.h"

int main() {
	Bank* bank = new Bank();
	char input[MAX];
	int id, balance;
	char name[MAX];

	while (true) {
		cout << "\n명령어를 입력해주세요.\nC: 계좌 개설\nD: 입금\nW: 출금\nI: 전체 고객 잔액 조회\nQ: 종료\n\n";
		cin >> input;
		
		if (input[0] == 'Q' || input[0] == 'q') break;
		
		else if (input[0] == 'C' || input[0] == 'c') {
			cout << "계좌 개설을 선택하셨습니다. 계좌 정보를 입력해주세요. \n계좌번호: ";
			cin >> id;
			cout << "\n성함: ";
			cin >> name;
			cout << "\n잔액: ";
			cin >> balance;
			cout << "\n\n";
			bank->CreateAccount(id, name, balance);
			cout << "계좌번호: " << id << " 성함: " << name << " 잔액: " << balance << " 으로 계좌 개설을 완료했습니다.\n";
		}

		else if (input[0] == 'D' || input[0] == 'd') {
			cout << "입금을 선택하셨습니다. 입금하실 계좌 정보를 입력해주세요.\n계좌번호: ";
			cin >> id;
			cout << "\n입금하실 금액을 입력해주세요.\n입금 금액: ";
			cin >> balance;
			bank->Deposit(id, balance);
		}

		else if (input[0] == 'W' || input[0] == 'w') {
			cout << "출금을 선택하셨습니다. 출금하실 계좌 정보를 입력해주세요.\n계좌번호: ";
			cin >> id;
			cout << "\n출금하실 금액을 입력해주세요.\n출금 금액: ";
			cin >> balance;
			bank->Withdraw(id, balance);
		}

		else if (input[0] == 'I' || input[0] == 'i'){
			cout << "전체 고객 잔액 조회를 선택하셨습니다.\n";
			bank->Inquire();
		}

		else {
			cout << "올바른 명령어를 입력해주세요.\n";
		}

	}

	cout << "프로그램을 종료합니다.\n";
	delete bank;
	return 0;
}