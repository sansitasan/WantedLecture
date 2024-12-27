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

	Account(const Account& account) {
		this->id = account.id;
		this->balance = account.balance;
		size_t len = strlen(account.name) + 1;
		this->name = new char[len];
		strcpy_s(this->name, len, account.name);
	}

	int GetID() const {
		return id;
	}

	const char* GetName() const {
		return name;
	}

	int GetBalance() const {
		return balance;
	}

	virtual void Inquire() const {
		cout << name << "���� �ܾ��� "
			<< balance << "�� �Դϴ�.\n";
	}

	virtual int SetBalance(int value) {
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

	virtual ~Account() {
		if (name) 
		{
			delete[] name;
		}
	}

protected:
	int id;
	char* name;
	int balance;
};