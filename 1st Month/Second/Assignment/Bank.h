#pragma once
#include "AccountEnum.h"

class Account;

class Bank {
public:
	Bank() {

	}

	Bank(const Bank& bank);

	~Bank();

	const Account* CreateAccount(int id, const char* name, int nameLength, int balance, EAccountType type);

	void Deposit(int id, int value);

	void Deposit(const char* name, int value);

	void Withdraw(int id, int value);

	void Withdraw(const char* name, int value);

	void Inquire();

	int GetCustomerCount() const { return customerCount; }

	Account* GetCustomer(int idx) const { return customers[idx]; }

private:
	int customerCount = 0;
	Account* customers[100] = {};
};

