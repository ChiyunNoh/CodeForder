#include "SNUMusicSystem.h"

int main(void) {
  SNUMusicSystem SNUMusic("musicList.csv");

  SNUMusic.Loop();
  return 0;
}
