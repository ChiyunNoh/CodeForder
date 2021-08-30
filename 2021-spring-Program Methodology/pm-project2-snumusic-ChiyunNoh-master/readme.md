# 430.211 프로그래밍 방법론 : Project 2
_Student ID_: 2017-13092

_이 름_: 노치윤

## Introduction about code

이 프로그램은 사용자가 은행계좌를 직접 만들어 SNU Money를 충전하고, 이를 이용하여 SNUMusicSystem에서 음악을 살 수 있는 프로그램이다.
파일은 크게 5개로 구성이 된다.

1. __Bank.cpp__

    - 이 파일은 사용자의 계좌에 대한 정보를 저장하는 파일.
    - Member Variable : string bankName (은행 계좌 이름), int  balance (잔고)


2. __Card.cpp__

    - 사용자가 설정한 카드의 정보를 저장하는 파일.
    - Member Variable : string cardName (사용자가 지정한 카드이름),  BankAccount \*  withdrawalAccount (카드의 출금계좌)

3. __Client.cpp__

    - SNUMusicSystem을 사용하는 사용자에 대한 정보를 저장하는 파일.
    - Member Variable 
      - string clientName (사용자 이름), int SNUMoey (충전된 SNUMoney),int numAlbums (소유한 앨범의 개수)
      - BakAccount \* accountList[5] (사용자가 등록한 계좌 정보, 만일 5개 이상 등록하거나, 같은 이름의 계좌 등록시 메시지를 오류 표시하도록 구현함)
      - Card \* cardList[5] (사용자가 등록한 카드의 정보, 만일 5개 이상 등록하거나 같은 이름의 카드 등록시 오류 메시지를 표시하도록 구현함)
      - Album albumList[100] (소유한 앨범의 리스트)
  
4. __Music.cpp__

    - 앨범과 음악에 대한 정보, 그리고 이에 대한 정보를 얻기위한 메소드를 구현한 파일.
    - _class Music_
      - Member Variabe: string musicName (노래 제목), Album \* album (자신이 속한 앨범), bool owned (사용자가 음악을 가졌는지에 대한 여부)
    - _class Album_
      - Member Variable : string albumName (앨범 제목), string artistName (가수 이름), int numMusic (수록곡의 개수), Music\*\* musicList (앨범을 가리키는 포인터들의 배열)

5. __SNUMusicSystem.cpp__

    - 실제로 SNUMusicSystem이 실행되기 위해 필요한 메소드들을 정의, 구현해 놓은 파일.
    - Member Variable : Client \* client (이 시스템을 사용하는 사용자), Album \* \* albumList (시스템 내 저장된 앨범들), int numAlbum (시스템 내 저장된 앨범의 수)

