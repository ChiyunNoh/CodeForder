#include "card.h"

Card::Card(const std::string name, BankAccount* account): cardName(name),withdrawalAccount(account){

}

const std::string& Card::GetName() const {
	return cardName;
}

BankAccount* Card::GetBankAccount() const {
	return withdrawalAccount;
}

bool Card::Pay(const int money) const {
	int remain=withdrawalAccount->GetBalance();
	if (remain < money) {
		return false;
	}
	else {
		remain -= money;
		withdrawalAccount->setBalance(remain);
		return true;
	}
}
