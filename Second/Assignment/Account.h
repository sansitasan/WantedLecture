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
			cout << "���� �ܾ��� " << ret << "�� �Դϴ�.\n";
			balance = ret;
		}

		else {
			cout << "ã���÷��� �ݾ��� ���� �ܾ��� " << balance << " ���� �����ϴ�.\n";
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
			cout << "�� ������ ���� �ִ�ġ�Դϴ�!\n";
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

		cout << "ã���ô� ���� ������ �������� �ʽ��ϴ�!\n";
	}

	void Deposit(const char* name, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (!strcmp(customers[i]->GetName(), name)) {
				customers[i]->SetBalance(value);
				return;
			}
		}

		cout << "ã���ô� ���� ������ �������� �ʽ��ϴ�!\n";
	}

	void Withdraw(int id, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (customers[i]->GetID() == id) {
				customers[i]->SetBalance(-value);
				return;
			}
		}

		cout << "ã���ô� ���� ������ �������� �ʽ��ϴ�!\n";
	}

	void Withdraw(const char* name, int value) {
		for (int i = 0; i < customerCount; ++i) {
			if (!strcmp(customers[i]->GetName(), name)) {
				customers[i]->SetBalance(-value);
				return;
			}
		}

		cout << "ã���ô� ���� ������ �������� �ʽ��ϴ�!\n";
	}

	void Inquire() {
		for (int i = 0; i < customerCount; ++i) {
			cout << customers[i]->GetName() << "�� �ܾ��� "
				<< customers[i]->GetBalance() << "�� �Դϴ�.\n";
		}
	}

private:
	int customerCount = 0;
	Account* customers[MAX] = {};
};