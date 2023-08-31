int ledpins[] = {5, 6, 9, 10};
const int ledCount = sizeof(ledpins) / sizeof(int);
int inputpin = 12;
int statuspin = 2;

int intensity = 0;
int delta = 1;
int maxIntensity = 20;
const int overflowIntensity = 100;

bool inputEventPending = false;
bool inputEventProcessed = false;

void setup() {
  pinMode(inputpin, INPUT);
  pinMode(statuspin, OUTPUT);
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledpins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void nextMode() {
  maxIntensity += 20;

  if (maxIntensity > overflowIntensity) {
    maxIntensity = 0;
  }

  modeChange();    
}

void prevMode() {
  maxIntensity -= 20;

  if (maxIntensity < 0) {
    maxIntensity = 100;  
  }

  modeChange();    
}

void modeChange() {
    intensity = 0;
    delta = 1;

    if (maxIntensity == 0) {
      Serial.println("no blink mode");
    } else {
      Serial.print("maxIntensity:");
      Serial.println(maxIntensity);        
    }
}

void statusBlink() {
  digitalWrite(statuspin, HIGH);
  delay(200);
  digitalWrite(statuspin, LOW);
  delay(50);
}

void nextStepBlink() {
  //Main logic: sending voltage to LEDs
  for (int i = 0; i < ledCount; i++) {
    analogWrite(ledpins[i], map(intensity, 0, 100, 0, 255));      
  }
  delay(25);

  if (intensity == maxIntensity && delta == 1) {
    delta = -1;
  } else if (intensity == 0 && delta == -1) {
    delta = 1;
  } else {
    intensity += delta;
  }
}

void nextStepNoBlink() {
  int adcValue = analogRead(A0);
  for (int i = 0; i < ledCount; i++) {
    analogWrite(ledpins[i], map(adcValue, 0, 1023, 0, 255));      
  }
}

void loop() {
  if (digitalRead(inputpin)==LOW) {
    inputEventPending = false;
  } else {
    if (!inputEventPending) {
      inputEventPending = true;
      inputEventProcessed = false;
      statusBlink();
    }
  }

  if (!inputEventProcessed) {
    inputEventProcessed = true;
    nextMode();
  }

  while (Serial.available()){
    char nextChar = Serial.read();

    if (nextChar == '+') {
      nextMode();
      statusBlink();
    }

    if (nextChar == '-') {
      prevMode();
      statusBlink();
    }
  }

  if (maxIntensity == 0) {
    nextStepNoBlink();
  } else {
    nextStepBlink();
  }
}
