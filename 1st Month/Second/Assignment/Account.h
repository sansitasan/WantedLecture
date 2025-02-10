#pragma once
#include "AccountEnum.h"
#include <iostream>
#define MAX 100

using namespace std;
class Bank;

class Account {
public:
	Account(int id, const char* name, int nameLength, int balance)
		: accountType(EAccountType::Normal), id(id), balance(balance), nameLength(nameLength) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	Account(const Account& account) {
		accountType = account.accountType;
		id = account.id;
		balance = account.balance;
		size_t len = strlen(account.name) + 1;
		name = new char[len];
		nameLength = len;
		strcpy_s(name, len, account.name);
	}

	EAccountType GetType() const {
		return accountType;
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

	int GetnameLength() const {
		return nameLength;
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
	EAccountType accountType;
	int id;
	char* name;
	int nameLength;
	int balance;
};