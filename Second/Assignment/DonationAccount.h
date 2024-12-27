#pragma once
#include "Account.h"

class DonationAccount : public Account
{
public:
	DonationAccount(int id, const char* name, int balance)
		: Account(id, name, balance), donation(0.01f * balance) {
		this->balance *= 0.99f;
	}

	virtual int SetBalance(int value) override {
		if (value > 0) { 
			value *= 0.99f;
			donation += 0.01f * value;
		}
		return Account::SetBalance(value);
	}

	virtual void Inquire() const override {
		Account::Inquire();
		cout << "��ε� �ݾ��� " << donation << "�� �Դϴ�.\n";
	}

private:
	int donation;
};

