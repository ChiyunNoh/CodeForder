#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <iostream>

#include "bank.h"
#include "card.h"
#include "music.h"

class Client {
public:
  Client(const std::string& name);

  //** DO NOT MODIFY THIS PART **//
  // delete copy constructor and assignment operator
  // bank account cannot be copied!
  Client(const Client&) = delete;
  Client& operator=(const Client&) = delete;
  //*****************************//

  // You need to implement destructor manually
  // Why?
  ~Client();

  const std::string& GetClientName() const;

  // return how much SNUMoney client has
  int GetSNUMoney() const;

  // get index-th (0~4) BankAccount pointer
  BankAccount* GetBankAccount(int accountIndex) const;

  // get index-th (0~4) Card pointer
  Card* GetCard(int cardIndex) const;

  // get numAlbums
  int GetNumAlbums() const;

  // get index-th (0~99) Album reference
  Album& GetAlbum(int albumIndex);

  // prints the list of bank accounts
  void PrintBankAccountList() const;

  // prints the list of cards
  void PrintCardList() const;

  // prints the list of musics
  void PrintMusicList() const;

  // charge SNUMoney from BandAccount balance
  bool ChargeSNUMoney(int money, int accountIndex);

  // Create and Add Bank Account to the list
  // fails if already 5 accounts are registered
  void AddBankAccount(std::string bankName, int money);

  // Create and Add Card to the list
  // 
  // fails if already 5 cards are registered
  bool AddCard(std::string cardName, int bankIndex);

  // pay for the price by SNUMoney
  // used internally in the class only
  bool PayBySNUMoney(int money);

  // pay for the price by card
  // used internally in the class only
  bool PayByCard(int money, int cardIndex);

  // add a whole album to the albumList
  bool AddAlbum(const Album& album);

  // add music to the albumList
  bool AddMusic(Music& music);

private:
  const std::string clientName;

  // you can charge SNUMoney by withdrawing money from bank accounts.
  // you cannot charge with cards.
  int SNUMoney; 

  // you cannot pay directly from bank accounts.
  // you have to first charge SNUMoney, then use SNUMoney to pay.
  
  // This array should be filled 
  BankAccount* accountList [5]; // you can register upto 5 bank accounts
  
  // you can use cards to pay money.
  // all cards are debit cards(check cards).
  Card* cardList [5]; // you can register upto 5 cards

  // you can have at most 100 albums
  // purchaed album & music will be added to this array
  Album albumList [100];

  // number of albums the client have
  int numAlbums;
};

#endif // CLIENT_H_

