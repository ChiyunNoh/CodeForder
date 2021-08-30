#ifndef CARD_H_
#define CARD_H_

#include <string>

#include "bank.h"

// This is not a credit card.
// It is a debit card(check card).
// One cannot use more money than tha bank deposit.
class Card {
public:
  // BankAccount should be made before the card
  Card(const std::string name, BankAccount* account);

  //** DO NOT MODIFY THIS PART **//
  // delete copy constructor and assignment operator
  // bank account cannot be copied!
  Card(const Card&) = delete;
  Card& operator=(const Card&) = delete;
  //*****************************//

  // get the card name
  const std::string& GetName() const;

  // get the BankAccount pointer
  BankAccount* GetBankAccount() const;
  
  // pay the money for the product
  bool Pay(const int money) const;

private:
  const std::string cardName; // name of the card (in English)
  BankAccount* withdrawalAccount; // associated bank account
};


#endif // CARD_H_
