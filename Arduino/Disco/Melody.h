class Melody {
  private:
    int* score;
    int scoreSize;
    int tempo;
    int wholeNote;
    int currNoteIdx = -2;
    int currNoteDuration = 0;
    
  public:
    Melody(int* melodyScore, int melodySize, int melodyTempo) : score(melodyScore), scoreSize(melodySize), tempo(melodyTempo), wholeNote((60000 * 4) / tempo) {
      next();
    }

    void next() {
      currNoteIdx = (currNoteIdx + 2) % (scoreSize * 2);
      int divider = score[currNoteIdx + 1];
      
      if (divider > 0) {
        currNoteDuration = (wholeNote) / divider;
      } else if (divider < 0) {
        currNoteDuration = (wholeNote) / abs(divider);
        currNoteDuration *= 1.5;
      }
    }

    int getTone() {
      return score[currNoteIdx];
    }

    int getDuration() {
      return currNoteDuration;
    }
};
