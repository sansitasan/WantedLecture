#pragma once
#include <iostream>
#define MAX 100

using namespace std;

class Account {
public:
	Account(int id, const char* name, int balance)
		: id(id), balance(balance) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	int GetID() {
		return id;
	}

	const char* GetName() {
		return name;
	}

	int GetBalance() {
		return balance;
	}

	int SetBalance(int value) {
		int ret = balance + value;
		if (ret > 0) {
			cout << "현재 잔액은 " << ret << "원 입니다.\n";
			balance = ret;
		}

		else {
			cout << "찾으시려는 금액이 현재 잔액인 " << balance << " 보다 많습니다.\n";
			ret = -1;
		}

		return ret;
	}


	~Account() {
		delete[] name;
	}

private:
	int id;
	char* name;
	int balance;
};

class Bank {
public:
	Bank() {

	}

	~Bank() {
		for (int i = 0; i < customerCount; ++i) {
			delete customers[i];
		}
	}

	void CreateAccount(int id, const char* name, int balance) {
		if (customerCount >= MAX) {
			cout << "고객 정보의 수가 최대치입니다!\n";
			return;
		}

		Account* newCustomer = new Account(id, name, balance);
		customers[customerCount++] = newCustomer;
	}

	void Deposit(int id, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (customers[i]->GetID() == id) {
				customers[i]->SetBalance(value);
				return;
			}
		}

		cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
	}

	void Deposit(const char* name, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (!strcmp(customers[i]->GetName(), name)) {
				customers[i]->SetBalance(value);
				return;
			}
		}

		cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
	}

	void Withdraw(int id, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (customers[i]->GetID() == id) {
				customers[i]->SetBalance(-value);
				return;
			}
		}

		cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
	}

	void Withdraw(const char* name, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (!strcmp(customers[i]->GetName(), name)) {
				customers[i]->SetBalance(-value);
				return;
			}
		}

		cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
	}

	void Inquire() {
		for (int i = 0; i < customerCount; ++i) {
			cout << customers[i]->GetName() << "의 잔액은 "
				<< customers[i]->GetBalance() << "원 입니다.\n";
		}
	}

private:
	int customerCount = 0;
	Account* customers[MAX] = {};
};