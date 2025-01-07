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
	const char* type = "type: %d\n";
	const char* intValue = "id: %d\nbalance: %d\nnameLength: %d\n";
	const char* donationIntValue = "id: %d\nbalance: %d\ndonation: %d\nnameLength: %d\n";
	const char* name = "name: %s\n\n";
};