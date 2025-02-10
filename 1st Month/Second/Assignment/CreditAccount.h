#pragma once
#include "Account.h"

class CreditAccount : public Account
{
public:
	CreditAccount(int id, const char* name, int nameLength, int balance)
		: Account(id, name, nameLength, balance) {
		accountType = EAccountType::Credit;
		interest = balance * 0.01;
	}

	virtual int SetBalance(int value) override {
		if (value > 0) { 
			interest += value * 0.01; 
			return Account::SetBalance(value + interest);
		}

		return Account::SetBalance(value);
	}

private:
	int interest;
};

