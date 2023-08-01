#include "RandomColor.h"

class FloatingColor {
  private:
    RandomColor randomR = RandomColor(8);
    RandomColor randomG = RandomColor(16);
    RandomColor randomB = RandomColor(24);

  public:
    void writeColorToPins(int ledPinR, int ledPinG, int ledPinB) {
      analogWrite(ledPinR, randomR.next());
      analogWrite(ledPinG, randomG.next());
      analogWrite(ledPinB, randomB.next());
    }
};