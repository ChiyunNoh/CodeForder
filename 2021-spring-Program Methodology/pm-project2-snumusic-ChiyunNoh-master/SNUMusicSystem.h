#ifndef SNUMUSICSYSTEM_H_
#define SNUMUSICSYSTEM_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "music.h"
#include "client.h"

class SNUMusicSystem {
public:
  SNUMusicSystem(std::string filename);

  //** DO NOT MODIFY THIS PART **//
  // delete copy constructor and assignment operator
  // SNUMusicSystem cannot be copied!
  SNUMusicSystem(const SNUMusicSystem&) = delete;
  SNUMusicSystem& operator=(const SNUMusicSystem&) = delete;
  //*****************************//

  // You need to implement destructor manually
  // Why?
  ~SNUMusicSystem();

  // the main loop
  void Loop();

  // service 0
  void PrintEntireAlbumList();
  // service 1
  void PurchaseAlbum();
  // service 2
  void PurchaseSong();
  // service 4
  void PrintSNUMoney();
  // service 5
  void ChargeSNUMoney();
  // service 6
  void RegisterBankAccount();
  // service 7
  void RegisterCard();


private:
  Client* client; // client (only one person)
  Album** albumList; // list of all albums in the SNU Music System
  int numAlbum; // number of all albums

  // For Students: You do not need to know what the functions
  // below this line does. 
  // -------------------------------------------------------------
  
  // Load Music List and Parse Them
  void _LoadMusicList(std::string filename);

  // Initialize Client
  void _Initialize();
};

#endif //SNUMUSICSYSTEM_H_

