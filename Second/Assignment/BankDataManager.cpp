#include "BankDataManager.h"
#include "Bank.h"
#include "DonationAccount.h"

BankDataManager::BankDataManager()
{
}

BankDataManager::~BankDataManager()
{
	delete[] fileLocation;
	delete[] donationFormat;
	delete[] format;
}

void BankDataManager::LoadData(Bank& bank)
{
	FILE* file = nullptr;
	fopen_s(&file, fileLocation, "rt");
	if (!file) return;

	fclose(file);
}

void BankDataManager::SaveData(Bank& bank)
{
	FILE* file = nullptr;
	fopen_s(&file, fileLocation, "wt");
	if (!file) return;

	const int accountCount = bank.GetCustomerCount();
	for (int i = 0; i < accountCount; ++i) {
		Account* account = bank.GetCustomer(i);
		char buffer[1024];
		switch (account->GetType())
		{
		case EAccountType::Donation:
			DonationAccount* donationAccount = dynamic_cast<DonationAccount*>(account);
			if (!donationAccount) continue;
			snprintf(buffer, 1024, donationFormat, donationAccount->GetType(), donationAccount->GetID(), 
				donationAccount->GetName(), donationAccount->GetBalance(), donationAccount->GetDonation());
			break;
		default:
			snprintf(buffer, 1024, format, account->GetType(), account->GetID(), account->GetName(), account->GetBalance());
			break;
		}
	}

	fclose(file);
}
