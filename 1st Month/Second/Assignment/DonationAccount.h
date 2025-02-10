#pragma once
#include "Account.h"

class DonationAccount : public Account
{
public:
	DonationAccount(int id, const char* name, int nameLength, int balance)
		: Account(id, name, nameLength, balance), donation(0.01 * balance) {
		accountType = EAccountType::Donation;
		this->balance *= 0.99;
	}

	virtual int SetBalance(int value) override {
		int ret = Account::SetBalance(value);
		if (value > 0) {
			value *= 0.99;
			donation += 0.01 * value;
			cout << "��ε� �� �ݾ��� " << donation << "�� �Դϴ�.\n";
		}

		return ret;
	}

	virtual void Inquire() const override {
		Account::Inquire();
		cout << "��ε� �� �ݾ��� " << donation << "�� �Դϴ�.\n";
	}

	int GetDonation() const {
		return donation;
	}

private:
	int donation;
};