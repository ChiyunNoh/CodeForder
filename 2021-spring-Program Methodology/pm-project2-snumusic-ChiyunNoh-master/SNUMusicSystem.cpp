#include "SNUMusicSystem.h"

SNUMusicSystem::~SNUMusicSystem() {
    for (int i = 0; i < numAlbum; i++) {
        for(int j = 0; j < albumList[i]->GetNumMusic(); j++) {
            delete albumList[i]->GetMusicList()[j];
         }
        delete albumList[i];
    }

    delete[] albumList;
    delete client;
  
}

void SNUMusicSystem::Loop() {
  while(true) {
    std::cout << std::endl
    << "Choose Service"<< std::endl 
    << "  0: Show entire album list" << std::endl
    << "  1: Purchase an entire album" << std::endl
    << "  2: Purchase a song" << std::endl
    << "  3: View my song list" << std::endl
    << "  4: View my SNU Money balance" << std::endl
    << "  5: Charge SNU Money" << std::endl
    << "  6: Register a bank account to SNU PAY" << std::endl
    << "  7: Register a card to SNU PAY" << std::endl
    << "  8: View my bank account list" << std::endl
    << "  9: View my card list" << std::endl;

    std::cout << "What service do you need?: ";
    int choice;
    std::cin >> choice;

    std::cout << std::endl;
    if(choice == 0) PrintEntireAlbumList();
    else if(choice == 1) PurchaseAlbum();
    else if(choice == 2) PurchaseSong();
    else if(choice == 3) client->PrintMusicList();
    else if(choice == 4) PrintSNUMoney();
    else if(choice == 5) ChargeSNUMoney();
    else if(choice == 6) RegisterBankAccount();
    else if(choice == 7) RegisterCard();
    else if(choice == 8) client->PrintBankAccountList();
    else if(choice == 9) client->PrintCardList();
    else if (choice == 10) break;
    else {
      std::cout << "Wrong Input, Choose Again!" << std::endl;
    } 
  }
}

// service 0
void SNUMusicSystem::PrintEntireAlbumList(){
  for(int i = 0; i < numAlbum; i++) {
    std::cout << std::right << std::setw(4) << i << ". ";
    albumList[i]->PrintAlbumName();
  }
}

// service 1
void SNUMusicSystem::PurchaseAlbum(){
  PrintEntireAlbumList();
  std::cout << "Choose the album number: ";
  int albumNumber;
  std::cin >> albumNumber;
  if(albumNumber < 0 || albumNumber >= numAlbum) {
    std::cout << "Wrong Album Number!" << std::endl;
    return;
  }
  else {
      int n = client->GetNumAlbums();
      int price= 700 * (albumList[albumNumber]->GetNumMusic());
      bool hasAlbum = false;
      for (int i = 0; i < n; i++) {
          if (client->GetAlbum(i) == *albumList[albumNumber]) {
              hasAlbum = true;
              if (client->GetAlbum(i).GetNumMusic() == albumList[albumNumber]->GetNumMusic()) {//already have entire album
                  std::cout << "You already have same album";
                  return;
              }
              else {
                  int addmusic_num = -client->GetAlbum(i).GetNumMusic() + albumList[albumNumber]->GetNumMusic();
                  if (700 * (albumList[albumNumber]->GetNumMusic()) > 1000 * addmusic_num) {
                      price = 1000 * addmusic_num;
                  }
                  break;
              }
          }
      }
      if (hasAlbum == false&&price!=0) {
          if (client->GetSNUMoney() < price) {
              std::cout << "There is not enough money at SNU Pay" << std::endl;
              return;
          }
          else {
              client->AddAlbum(*albumList[albumNumber]);
              client->PayBySNUMoney(price);
              return;
          }
      }

  }


  // TODO
  // implement album purchasing management
  // and payment
  // this step can fail due to various reasons
  // -not enough SNUMoney balance, if SNUMoney was chosen
  // -not enough bank account balance for card payments
  // -wrong indices chosen
  // -client already have the album in the client's albumList
  // -etc
  // just return in those cases

  // price of a album: 700 * (number of songs in the album)
  // however, if the price of buying the songs, that the client
  // does not have, one by one is cheaper,
  // that price is applied.
  // i.e. 1000 * (number of songs in the album that client do not have)
  //
  // for example, when album is composed of 10 songs 
  // and the client already have 4 songs among them and
  // do not have only 6 songs,
  // 6000 won will be charged, not 7000 won.
}

// service 2
void SNUMusicSystem::PurchaseSong(){
  PrintEntireAlbumList();
  std::cout << "Choose the album number: ";
  int albumNumber;
  std::cin >> albumNumber;
  if(albumNumber < 0 || albumNumber >= numAlbum) {
    std::cout << "Wrong Album Number!" << std::endl;
    return;
  }

  // show the list of musics in the album
  albumList[albumNumber]->PrintMusics();

  std::cout << "Choose the track number: ";
  int trackNumber;
  std::cin >> trackNumber;
  
  if(trackNumber < 0 || trackNumber >= albumList[albumNumber]->GetNumMusic()) {
    std::cout << "Wrong Track Number!" << std::endl;
    return;
  }
  else {
      int n = client->GetNumAlbums();
      int price = 1000;
      for (int i = 0; i < n; i++) {
          if (client->GetAlbum(i) == *albumList[albumNumber]) {//there is same album in client's albumlist
              if (client->GetAlbum(i).GetMusicList()[trackNumber]->IsOwned()) {//there is same music
                  std::cout << "You already have the same music." << std::endl;
                  return;
              }
          }
      }

      if (client->GetSNUMoney() < price) {
          std::cout << "There is not enough money at SNU Pay" << std::endl;
          return;
      }
      else {
          client->AddMusic(*albumList[albumNumber]->GetMusicList()[trackNumber]);
          //client->GetAlbum(albumNumber).SetOneSongOwned(trackNumber);
          client->PayBySNUMoney(price);
          return;
      }
  }
      // TODO
  
  // implement song purchasing management
  // and payment
  // this step can fail due to various reasons
  // -not enough SNUMoney balance, if SNUMoney was chosen
  // -not enough bank account balance for card payments
  // -wrong indices chosen
  // -client already have that song in the client's albumList
  // -etc
  // just return in those cases
  // price of a song: 1000 won 
}
// service 4
void SNUMusicSystem::PrintSNUMoney(){
  std::cout << "My SNU Money balance: " << client->GetSNUMoney()
            << " Won." << std::endl;
}
// service 5
void SNUMusicSystem::ChargeSNUMoney(){
  std::cout << "How much money do you want to charge?: ";
  int money;
  std::cin >> money;

  client->PrintBankAccountList();
  std::cout << "Charge from which account?: ";
  int accountIndex;
  std::cin >> accountIndex;
  if (client->ChargeSNUMoney(money, accountIndex)) {//success to charge snumoney
      return;
  }
  std::cout << "fail!" << std::endl;
  return;
  // TODO
  // implement SNU Money charging process
  // this step can fail due to various reasons
  // -low bank account balance, etc 
}


// service 6
void SNUMusicSystem::RegisterBankAccount(){
    std::cout << "Which bank account do you want to register?";
    std::string bankname;
    std::cin >> bankname;
    std::cout << "How much do you want to deposit?";
    int money;
    std::cin >> money;
    client->AddBankAccount(bankname, money);
    return;
  // TODO
  // register bank account to Client Class
}
// service 7
void SNUMusicSystem::RegisterCard(){
    std::cout << "Which card do you want to register?";
    std::string card;
    std::cin >> card;
    std::cout << "Which index of bank do you want to use?";
    int bankIndex;
    std::cin >> bankIndex;
    client->AddCard(card, bankIndex);
    return;
  // TODO
  // register card to Client Class
}




// For Students: You do not need to know what the functions
// below this line does. 
// -------------------------------------------------------------  

SNUMusicSystem::SNUMusicSystem(std::string filename) {
  _LoadMusicList(filename);
  _Initialize();
}

void SNUMusicSystem::_Initialize() {
  std::cout << "Welcome to SNU Music System!" << std::endl;
  // ASCII Art LoL
  std::cout
  << "     _______..__   __.  __    __     .___  ___.  __    __       _______. __    ______ " << std::endl
  << "    /       ||  \\ |  | |  |  |  |    |   \\/   | |  |  |  |     /       ||  |  /      |" << std::endl
  << "   |   (----`|   \\|  | |  |  |  |    |  \\  /  | |  |  |  |    |   (----`|  | |  ,----'" << std::endl
  << "    \\   \\    |  . `  | |  |  |  |    |  |\\/|  | |  |  |  |     \\   \\    |  | |  |     " << std::endl
  << ".----)   |   |  |\\   | |  `--'  |    |  |  |  | |  `--'  | .----)   |   |  | |  `----." << std::endl
  << "|_______/    |__| \\__|  \\______/     |__|  |__|  \\______/  |_______/    |__|  \\______|" << std::endl
  << "                                                                                      " << std::endl;
  
  std::cout << "Enter Your Name: ";
  char nameBuffer[100];
  std::cin.getline(nameBuffer, 100);
  client = new Client(nameBuffer);
}

// Load Music List and Parse Them
// For Students: You do not need to know what this function does
void SNUMusicSystem::_LoadMusicList(std::string filename) {
  std::ifstream musicListFile(filename);
  if(!musicListFile) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    std::cerr << "Check file path." << std::endl;
    exit(1);
  }
  // the csv list is long: 100 lines
  // but may contain duplicate albums
  // so just use 50 albums for siplicity
  numAlbum = 50;
  albumList = new Album* [numAlbum];

  // input csv format
  // albumName[;]artistName[;][/]Track1[/]Track2[/]...[/]TrackN[\r][\n]

  int albumIndex = 0;
  std::string musicBuffer [40]; // temporary track holder
  while (musicListFile.peek() != EOF && albumIndex < numAlbum) {
    std::string albumName, artistName, entireTracks;
    std::getline(musicListFile, albumName, ';');
    std::getline(musicListFile, artistName, ';');
    std::getline(musicListFile, entireTracks);

    entireTracks.erase(0,1);
    int posReturnCarriage = entireTracks.find('\r');
    if(posReturnCarriage != std::string::npos) {
      entireTracks.erase(posReturnCarriage, 1);
    }
    entireTracks = entireTracks + "/";
    int nameStart = 0;
    int nameEnd = entireTracks.find('/');
    // parse track string and split into musicBuffer
    int trackIndex = 0;
    while(nameEnd != std::string::npos && trackIndex < 40) {
      musicBuffer[trackIndex] = entireTracks.substr(nameStart, nameEnd - nameStart);
      nameStart = nameEnd + 1;
      nameEnd = entireTracks.find('/', nameStart);
      trackIndex += 1;
    }
    // check if the same album already exists in the albumList
    bool duplicate = false;
    for(int i=0; i < albumIndex; i++) {
      if(albumList[i]->GetAlbumName() == albumName &&
          albumList[i]->GetArtistName() == artistName) {
        duplicate = true;
        break;
      }
    }
    // fill in album information
    if(duplicate == false) {
      albumList[albumIndex] = new Album(albumName, artistName, trackIndex);
      for(int i = 0; i < trackIndex; i++) {
        (albumList[albumIndex]->GetMusicList())[i] = new Music(musicBuffer[i], albumList[albumIndex]);
      }

      albumIndex += 1;
    }
  }
}

