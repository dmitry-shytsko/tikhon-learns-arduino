#include <LiquidCrystal_I2C.h>
#include <dht.h>

dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 12;
const int echoPin = 11;
const int dhtPin = 2;

const int maxDistance = 1000;
const float timeOut = maxDistance * 60;
const int soundVelocity = 340;

void setup() {
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  
  lcd.init(); 
  lcd.backlight(); 

  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0,0);
  
  if (DHT.read11(dhtPin) == DHTLIB_OK) {
    lcd.print("Climate:");
    lcd.print(int(DHT.temperature));
    lcd.print("C ");
    lcd.print(int(DHT.humidity));
    lcd.print("% ");
    lcd.print("                ");
  } else {
    lcd.print("Sensor Error    ");
  }
  
  
  
  
  
 
  
  int sonar = (int)getSonar();
  lcd.setCursor(0, 1);
  if (sonar <= 500) {
    lcd.print(sonar);
    lcd.print(" cm");
  } else {
    lcd.print("Nothing here");
  }
  lcd.print("                ");
  delay(150);  
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTime = pulseIn(echoPin, HIGH, timeOut);
  distance = (float)pingTime * soundVelocity / 2 / 10000;
  return distance;
}
