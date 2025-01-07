#include "BankDataManager.h"
#include "Bank.h"
#include "DonationAccount.h"

BankDataManager::BankDataManager()
{
}

BankDataManager::~BankDataManager()
{

}

void BankDataManager::LoadData(Bank& bank)
{
	FILE* file = nullptr;
	fopen_s(&file, fileLocation, "rt");
	if (!file) return;
	int id, balance, donation, nameLegnth;
	EAccountType Etype;
	char nameA[50];
	char buffer[1024];

	while (fscanf_s(file, type, &Etype) == 1) {
		donation = 0;
		if (Etype == EAccountType::Donation) {
			fscanf_s(file, donationIntValue, &id, &balance, &donation, &nameLegnth);
		}
		else {
			fscanf_s(file, intValue, &id, &balance, &nameLegnth);
		}
		fscanf_s(file, name, nameA, nameLegnth + 1);
		bank.CreateAccount(id, nameA, nameLegnth, balance + donation, Etype);
	}
	
	fclose(file);
}

void BankDataManager::SaveData(Bank& bank)
{
	FILE* file = nullptr;
	fopen_s(&file, fileLocation, "wt");
	if (!file) return;
	char buffer[1024];
	const int accountCount = bank.GetCustomerCount();
	int nameLength = 0;
	DonationAccount* donationAccount = nullptr;

	for (int i = 0; i < accountCount; ++i) {
		Account* account = bank.GetCustomer(i);
		donationAccount = nullptr;
		snprintf(buffer, 1024, type, account->GetType());
		fputs(buffer, file);
		memset(buffer, 0, 1024);

		nameLength = account->GetnameLength();

		switch (account->GetType())
		{
		case EAccountType::Donation:
			donationAccount = dynamic_cast<DonationAccount*>(account);
			if (!donationAccount) continue;
			snprintf(buffer, 1024, donationIntValue, donationAccount->GetID(), donationAccount->GetBalance(),
				donationAccount->GetDonation(), nameLength);
			break;
		default:
			snprintf(buffer, 1024, intValue, account->GetID(), account->GetBalance(), nameLength);
			break;
		}
		fputs(buffer, file);
		memset(buffer, 0, 1024);
		snprintf(buffer, 1024, name, account->GetName());
		fputs(buffer, file);
		memset(buffer, 0, 1024);
	}

	fclose(file);
}
