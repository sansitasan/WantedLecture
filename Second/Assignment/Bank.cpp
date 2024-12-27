#pragma once
#include <iostream>
#include "CreditAccount.h"
#include "DonationAccount.h"
#include "Bank.h"

Bank::Bank(const Bank& bank)
{
	customerCount = bank.customerCount;

	for (int i = 0; i < customerCount; ++i) {
		customers[i] = new Account(*bank.customers[i]);
	}
}

Bank::~Bank()
{
	for (int i = 0; i < customerCount; ++i) {
		delete customers[i];
	}
}

const Account* Bank::CreateAccount(int id, const char* name, int balance, EAccountType type)
{
	if (customerCount >= MAX) {
		cout << "고객 정보의 수가 최대치입니다!\n";
		return nullptr;
	}
	Account* newCustomer = nullptr;
	switch (type) {
		case EAccountType::Credit:
			newCustomer = new CreditAccount(id, name, balance);
			break;

		case EAccountType::Donation:
			newCustomer = new DonationAccount(id, name, balance);
			break;

		default:
			newCustomer = new Account(id, name, balance);
			break;
	}

	customers[customerCount++] = newCustomer;
	return newCustomer;
}

void Bank::Deposit(int id, int value)
{
	for (int i = 0; i < customerCount; ++i) {
		if (customers[i]->GetID() == id) {
			customers[i]->SetBalance(value);
			return;
		}
	}

	cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
}

void Bank::Deposit(const char* name, int value)
{
	for (int i = 0; i < customerCount; ++i) {
		if (!strcmp(customers[i]->GetName(), name)) {
			customers[i]->SetBalance(value);
			return;
		}
	}

	cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
}

void Bank::Withdraw(int id, int value)
{
	for (int i = 0; i < customerCount; ++i) {
		if (customers[i]->GetID() == id) {
			customers[i]->SetBalance(-value);
			return;
		}
	}

	cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
}

void Bank::Withdraw(const char* name, int value)
{
	for (int i = 0; i < customerCount; ++i) {
		if (!strcmp(customers[i]->GetName(), name)) {
			customers[i]->SetBalance(-value);
			return;
		}
	}

	cout << "찾으시는 고객의 정보가 존재하지 않습니다!\n";
}

void Bank::Inquire()
{
	for (int i = 0; i < customerCount; ++i) {
		customers[i]->Inquire();
	}
}
