#pragma once
#include "Account.h"

class CreditAccount : public Account
{
public:
	CreditAccount(int id, const char* name, int balance)
		: Account(id, name, balance) {
		accountType = EAccountType::Credit;
		this->balance *= 1.01f;
	}

	virtual int SetBalance(int value) override {
		if (value > 0) value *= 1.01f;
		return Account::SetBalance(value);
	}
};

