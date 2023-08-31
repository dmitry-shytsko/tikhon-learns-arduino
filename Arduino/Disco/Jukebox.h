#include "Melody.h"
#include "melodies.h"

Melody pinkPantherM(pinkPanther, pinkPantherSize, 120);
//Melody darthVaderM(darthVader, darthVaderSize, 108);
Melody nokiaM(nokia, nokiaSize, 108);
Melody godfatherM(godfather, godfatherSize, 108);
Melody tetrisM(tetris, tetrisSize, 108);
Melody allMelodies[] = {pinkPantherM, /*darthVaderM,*/ nokiaM, godfatherM, tetrisM};
int allMelodiesCount = 4;

class Jukebox {
  private:
    Melody *melodies;
    int melodyCount;
    int currMelodyIdx = 0;
    
  public:
    Jukebox(Melody *allMelodies, int allMelodiesCount) : melodies(allMelodies), melodyCount(allMelodiesCount) {}
  
    void next() {
      melodies[currMelodyIdx].next();
    }

    int getTone() {
      return melodies[currMelodyIdx].getTone();
    }

    int getDuration() {
      return melodies[currMelodyIdx].getDuration();
    }

    int nextMelody() {
      currMelodyIdx = (currMelodyIdx + 1) % melodyCount;
    }

    int prevMelody() {
      currMelodyIdx--;
      currMelodyIdx = max(currMelodyIdx, 0);
    }

    void playOnBuzzerWithDelay(int buzzerPin) {
      tone(buzzerPin, getTone(), getDuration() * 0.9);
      delay(getDuration());
      next();
    }
};
