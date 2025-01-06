#pragma once
#include <iostream>

class Account;
class Bank;

class BankDataManager
{
public:
	BankDataManager();
	~BankDataManager();

	void LoadData(Bank& bank);
	void SaveData(Bank& bank);
private:
	const char* fileLocation = "data.txt";
	const char* format = "type: %d\n id: %d\n name: %s\n balance: %d\n\n";
	const char* donationFormat = "type: %d\n id: %d\n name: %s\n balance: %d\n donation: %d\n\n";
};