#include "client.h"

Client::Client(const std::string& name) : clientName(name),
                                          SNUMoney(0),
                                          numAlbums(0) {
   
  
    for (int i = 0; i < 5; i++) {
        accountList[i] = new BankAccount("", 0);
        cardList[i] = new Card("", nullptr);
    }
   

}

Client::~Client() {
    for (int i = 0; i < 5; i++) {
        
        delete accountList[i];
    }
    for (int i = 0; i < 5; i++) {
        
        delete cardList[i];
    }
}

const std::string& Client::GetClientName() const {
  return clientName;
}

int Client::GetSNUMoney() const{
  return SNUMoney;
}

// this function can return nullptr
BankAccount* Client::GetBankAccount(int accountIndex) const {
  if(accountIndex >= 0 && accountIndex < 5) {
    return accountList[accountIndex];
  }
  else {
    return nullptr;
  }
}

// this function can return nullptr
Card* Client::GetCard(int cardIndex) const {
  if(cardIndex >= 0 && cardIndex < 5) {
    return cardList[cardIndex];
  }
  else {
    return nullptr;
  }
}

int Client::GetNumAlbums() const {
  return numAlbums;
}


Album& Client::GetAlbum(int albumIndex) {
    if (albumIndex >= 0 && albumIndex < 100) {
        return albumList[albumIndex];
    }
    
    
}


void Client::PrintBankAccountList() const {
  for(int i = 0; i < 5; i++) {
    if(accountList[i]->GetName() == "") {
      if(i == 0) {
        std::cout << "No bank account registered!" << std::endl;
      }
      break;
    }
    std::cout << i << ". " << accountList[i]->GetName() << std::endl;
  }
}

void Client::PrintCardList() const {
  for(int i = 0; i < 5; i++) {
    if(cardList[i]->GetName() == "") {
      if(i == 0) {
        std::cout << "No debit card registered!" << std::endl;
      }
      break;
    }
    std::cout << i << ". " << cardList[i]->GetName() << std::endl;
  }
}

void Client::PrintMusicList() const {
  for(int i = 0; i < numAlbums; i++) {
    albumList[i].PrintClientOwnedMusics();
  }
}

// This function charges SNUMoney by
// withdrawing money from a bank account.
// Study this function carefully!
bool Client::ChargeSNUMoney(int money, int accountIndex) {
  if(accountIndex < 0 || accountIndex >= 5) {
    return false;
  }
  if(accountList[accountIndex] == nullptr) {
    return false;
  }
  bool result = accountList[accountIndex]->Withdraw(money);
  if(result == true) {
    SNUMoney += money;
  }
  return result;
}

// *** README *** ///
// The accountList and cardList should be filled from index 0.
// When we remove an entry from the array, the array element
// should be filled with nullptr

// Also if the array was like
// 0. Woori
// 1. Sinhan
// 2. Hana
// 3. Nonghyup
// 4. nullptr

// After performing RemoveBankAccount(1)
// it should look like
// 0. Woori
// 1. Hana
// 2. Nonghyup
// 3. nullptr
// 4. nullptr
// after the removement.
// i.e. there should not be a blank nullptr space in between.
// the same rule applies for cardList.

// Note that removing entry mean destructing those entries.
// This is a little counter-intuitive 
// BE CAREFUL ABOUT MEMORY LEAKS!

void Client::AddBankAccount(std::string bankName, int money) {//create new bank account
    for (int i = 0; i < 5; i++) {
        if (accountList[i]->GetName() == bankName) { //already have
            std::cout << "이미 등록된 계좌 입니다." << std::endl;
            return;
        }
        else {
            if (accountList[i]->GetName()=="") {//the list is not full
              delete accountList[i];
              accountList[i] = new BankAccount(bankName, money);//o
              break;
              return;
            }
        }
        if(i==4){
          if(accountList[i]->GetName()!=""){
            std::cout<<"이미 5개의 계좌를 사용하셨습니다.";
            return;
          }
        }
    }
    return;

  // TODO
  // creates a BankAccount and put it into the list
  // fails if list is full
}

bool Client::AddCard(std::string cardName, int bankIndex) {
    for (int i = 0; i < 5; i++) {
        if (cardList[i]->GetName() == cardName) {
            std::cout << "이미 등록된 카드입니다." << std::endl;
            return false;
        }
        if (cardList[i]->GetName() == "") {
          delete cardList[i];
          cardList[i] = new Card(cardName, accountList[bankIndex]);
          return true;
        }
        if(i==4){
          if(cardList[i]->GetName()!=""){
            std::cout<<"이미 5개의 카드를 모두 사용하셨습니다.";
            return false;
          }
        }
    }
    return false;
    // TODO
  // creates a Card and put it into the list
  // note that the bank account associated with the card
  // must be in the accountList
  // fails if list is full or bank account does not exist for the index
}

bool Client::PayBySNUMoney(int money) {

    if (money > SNUMoney) {
        return false;
    }
    else{
        SNUMoney -= money;
        return true;
    }
  // TODO
  // pay money by SNU Money.
  // If charged SNUMoney is not enough,
  // the operation fails and returns false.
  // Otherwise, decrease charged SNUMoney 
  // and return true. 
}

bool Client::PayByCard(int money, int cardIndex) {
    if (cardList[cardIndex] == nullptr) {
        return false;
    }
    else {
        cardList[cardIndex]->GetBankAccount()->Withdraw(money);
        return true;
    }
    // TODO
  // pay money by debit card.
  // if the card for cardIndex does not exist or
  // the card-associated bank account has not enough balance, 
  // the operation fails and returns false.
}

bool Client::AddAlbum(const Album& album) {
    if (numAlbums == 100) {
        return false;//already has same album
    }
    for (int i = 0; i < GetNumAlbums(); i++) {
        if (GetAlbum(i) == album) {
            return false;//already has same album
        }
    }
    album.SetEntireAlbumOwned();
    albumList[numAlbums] = album;//add success
    numAlbums++;
    return true;
  // TODO
  // Copy the album to the albumList.
  // If the same album already exists,
  // copy to that position in the array albumList.
  // use overloaded == operator to check if the album is same.
  // i.e. do not keep duplicate copies of the same album.
}

bool Client::AddMusic(Music& music) {
    if (music.IsOwned()) {
        return false;
    }
    bool hasAlbum = false;
    int albumindex = -1;
    for (int i = 0; i < GetNumAlbums(); i++) {
        if (GetAlbum(i) == *(music.GetAlbum())) {//already has same album
            albumindex = i;
            hasAlbum = true;
            break;
        }
    }
    if (hasAlbum == true) {
        music.SetOwned();
    }
    else {
        albumList[numAlbums] = *music.GetAlbum();
        numAlbums++;
        music.SetOwned();
    }
    return false;


    
  // TODO
  // Copy the music to the albumList.
  // If the album of the music already exists,
  // copy to that position in the array albumList.
  // If not, create a new album entry in the array.
  // use overloaded == operator to check if the album is same.
  // i.e. do not keep duplicate copies of the same album.
}

