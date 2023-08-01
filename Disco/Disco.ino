#include "FloatingColor.h"
#include "Jukebox.h"

int ledPinR = 11;
int ledPinG = 10;
int ledPinB = 9;
int buzzerPin = 8;
int buttonPin = 2;
int infraPin = 6;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(infraPin, INPUT);
  Serial.begin(9600);
}

FloatingColor floatingColor;
Jukebox jukebox(allMelodies, allMelodiesCount);

const int NO_DISCO_MODE = 0;
const int DISCO_MODE_LIGHTS_ONLY = 1;
const int DISCO_MODE_CRAZY = 2;
const int DISCO_MODE_LIGHT_BASED = 3;
const int DISCO_MODE_INFRA = 4;
const int MODE_COUNT = 5;

int currentMode = DISCO_MODE_INFRA;

bool inputEventPending = false;
bool inputEventProcessed = false;

void checkMode() {
  if (digitalRead(buttonPin) == HIGH) {
    inputEventPending = true;
  } else {
    inputEventPending = false;
    inputEventProcessed = false;
  }

  if (inputEventPending && !inputEventProcessed) {
    currentMode = (currentMode + 1) % MODE_COUNT;
    Serial.print("Entering Mode: ");
    Serial.println(currentMode);
    inputEventProcessed = true;
  }
}

void loop() {  
  checkMode();

  bool discoLights = false;
  bool discoMusic = false;

  if (currentMode == DISCO_MODE_LIGHTS_ONLY) {
    discoLights = true;
  }

  if (currentMode == DISCO_MODE_CRAZY) {
    discoLights = true;
    discoMusic = true;
  }

  if (currentMode == DISCO_MODE_LIGHT_BASED) {
    int sveta_detect0r = map(analogRead(A5), 0, 1023, 0, 100);
    discoLights = sveta_detect0r > 30;
    discoMusic = sveta_detect0r > 30;
  }

  if (currentMode == DISCO_MODE_INFRA){
    int infraRead = digitalRead(infraPin);
    if (infraRead == HIGH) {
      discoLights = true;
      discoMusic = true;
    }
  }

  if (discoLights) {
    floatingColor.writeColorToPins(ledPinR, ledPinG, ledPinB);    

    if (discoMusic) {
      jukebox.playOnBuzzerWithDelay(buzzerPin);
    } else {
      delay(100);
    }
  } else {
    long newR = map(analogRead(A2), 0, 1023, 0, 255);
    long newG = map(analogRead(A1), 0, 1023, 0, 255);
    long newB = map(analogRead(A0), 0, 1023, 0, 255);
    analogWrite(ledPinR, newR);
    analogWrite(ledPinG, newG);
    analogWrite(ledPinB, newB);
  }

  noTone(buzzerPin);
}
