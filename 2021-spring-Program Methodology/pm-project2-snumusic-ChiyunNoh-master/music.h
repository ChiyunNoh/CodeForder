#ifndef MUSIC_H_
#define MUSIC_H_

#include <string>
#include <iostream>
#include <iomanip>

class Album;
class Music;

class Album {
public:
  Album(); // defulat constructor (used in client)
  Album(const std::string& _albumName,
        const std::string& _artistName,
        int _numMusic); // constructor

  Album(const Album& rhs); // copy constructor
  Album& operator=(const Album& rhs); // assignment operator
  ~Album(); // destructor

  // equalness checking operation
  // should be used in client.cpp
  // only check albumName and artistName
  bool operator== (const Album& rhs);

  // print album name
  void PrintAlbumName() const;
  // print list of musics
  void PrintMusics() const;
  // print list of musics that are owned by client 
  void PrintClientOwnedMusics() const;

  // Getter functions
  const std::string& GetAlbumName() const;
  const std::string& GetArtistName() const;
  int GetNumMusic() const;
  Music** GetMusicList() const;

  // Set owned when copying to client's albumList
  void SetEntireAlbumOwned() const;
  void SetOneSongOwned(int trackNumber) const;

private:
  std::string albumName; // album name
  std::string artistName; // artist name
  int numMusic; // number of musics in the album

  // list of pointers to musics in the album
  // i.e. Music* musicList [numMusic]
  Music** musicList; // should be dynamically allocated using numMusic
};

class Music {
public:
  Music(); // default constructor
  Music(const std::string& _musicName,
        Album* _album,
        bool _owned = false);

  // return music name
  const std::string& GetName() const;
  // return owned
  bool IsOwned() const;
  // return the album pointer
  Album* GetAlbum() const;

  // set the music track to owned
  void SetOwned();

private:
  std::string musicName;
  Album* album; // pointer to the album that this music belongs to
  bool owned;
  // 'owned' variable is very special
  // it signifies whether this music belongs to 
  // this value should be set to true only when the music
  // is copied to client's 
};

#endif // MUSIC_H_

