#include "bank.h"

BankAccount::BankAccount(const std::string name, int money):bankName(name), balance(money) {}

const std::string& BankAccount::GetName() const {
	return this->bankName;
}

int BankAccount::GetBalance() const {
	return this->balance;
}

void BankAccount::Deposit(const int money) {
	this->balance += money;
}
void BankAccount::setBalance(int money) {
	balance = money;
}

bool BankAccount::Withdraw(const int money) {
	if (balance < money) {
		return false;
	}
	else {
		balance -= money;
		return true;
	}
}
