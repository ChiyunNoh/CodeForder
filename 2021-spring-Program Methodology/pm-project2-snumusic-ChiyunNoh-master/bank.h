#ifndef BANK_H_
#define BANK_H_

#include <string>

class BankAccount {
public:
  BankAccount(const std::string name, int money);

  //** DO NOT MODIFY THIS PART **//
  // delete copy constructor and assignment operator
  // bank account cannot be copied!
  BankAccount(const BankAccount&) = delete;
  BankAccount& operator=(const BankAccount&) = delete;
  //*****************************//

  // get the bank name
  const std::string& GetName() const;

  // get the balance
  int GetBalance() const;

  // deposit money into the bank account
  void Deposit(const int money);

  // withdraw money from bank account
  bool Withdraw(const int money);

  void setBalance(int money);

private:
  const std::string bankName; // name of the bank (in English)
  int balance; // money in the bank account
};

#endif // BANK_H_
