#pragma once
#include "Account.h"
#include "Bank.h"
#include "BankDataManager.h"

EAccountType GetAccountType(char input) {
	if (input == 'C' || input == 'c') {
		return EAccountType::Credit;
	}

	else if (input == 'D' || input == 'd') {
		return EAccountType::Donation;
	}

	else
		return EAccountType::Normal;
}

int main() {
	Bank* bank = new Bank();
	char userInput[MAX];
	int id, balance;
	char name[MAX];

	BankDataManager dataManager;
	dataManager.LoadData(*bank);

	while (true) {
		cout << "\n명령어를 입력해주세요.\nC: 계좌 개설\nD: 입금\nW: 출금\nI: 전체 고객 잔액 조회\nQ: 종료\n\n";
		cin >> userInput;
		
		if (userInput[0] == 'Q' || userInput[0] == 'q') break;
		
		else if (userInput[0] == 'C' || userInput[0] == 'c') {
			cout << "계좌 개설을 선택하셨습니다. 계좌 정보를 입력해주세요. \nC: 신용 계좌\nD: 기부 계좌\nN: 일반 계좌\n";
			cin >> userInput;

			cout << "\n계좌번호: ";
			cin >> id;
			cout << "\n성함: ";
			cin >> name;
			cout << "\n잔액: ";
			cin >> balance;
			cout << "\n\n";

			const Account* account = bank->CreateAccount(id, name, balance, strlen(name), GetAccountType(userInput[0]));

			if (!account) continue;
			account->Inquire();
		}

		else if (userInput[0] == 'D' || userInput[0] == 'd') {
			cout << "입금을 선택하셨습니다. 입금하실 계좌 정보를 입력해주세요.\n계좌번호: ";
			cin >> id;
			cout << "\n입금하실 금액을 입력해주세요.\n입금 금액: ";
			cin >> balance;
			bank->Deposit(id, balance);
		}

		else if (userInput[0] == 'W' || userInput[0] == 'w') {
			cout << "출금을 선택하셨습니다. 출금하실 계좌 정보를 입력해주세요.\n계좌번호: ";
			cin >> id;
			cout << "\n출금하실 금액을 입력해주세요.\n출금 금액: ";
			cin >> balance;
			bank->Withdraw(id, balance);
		}

		else if (userInput[0] == 'I' || userInput[0] == 'i'){
			cout << "전체 고객 잔액 조회를 선택하셨습니다.\n";
			bank->Inquire();
		}

		else {
			cout << "올바른 명령어를 입력해주세요.\n";
		}

	}

	dataManager.SaveData(*bank);

	cout << "프로그램을 종료합니다.\n";
	delete bank;
	return 0;
}