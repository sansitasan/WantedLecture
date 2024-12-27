#pragma once
class Account;

class Bank {
public:
	enum EAccountType {
		None,
		Normal,
		Credit,
		Donation
	};

	Bank() {

	}

	Bank(const Bank& bank);

	~Bank();

	const Account* CreateAccount(int id, const char* name, int balance, EAccountType type);

	void Deposit(int id, int value);

	void Deposit(const char* name, int value);

	void Withdraw(int id, int value);

	void Withdraw(const char* name, int value);

	void Inquire();

private:
	int customerCount = 0;
	Account* customers[MAX] = {};
};

