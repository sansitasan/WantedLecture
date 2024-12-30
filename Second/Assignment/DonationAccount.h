#pragma once
#include "Account.h"

class DonationAccount : public Account
{
public:
	DonationAccount(int id, const char* name, int balance)
		: Account(id, name, balance), donation(0.01 * balance) {
		this->balance *= 0.99;
	}

	virtual int SetBalance(int value) override {
		if (value > 0) { 
			value *= 0.99;
			donation += 0.01 * value;
			cout << "��ε� �� �ݾ��� " << donation << "�� �Դϴ�.\n";
		}
		return Account::SetBalance(value);
	}

	virtual void Inquire() const override {
		Account::Inquire();
		cout << "��ε� �� �ݾ��� " << donation << "�� �Դϴ�.\n";
	}

private:
	int donation;
};

