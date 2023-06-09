#include <Keypad.h>
#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <TimerOne.h>

#define roomTemp 2
#define ambTemp 4
#define servoPin 3

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'#', '0', '*', 'D'}
};
byte rowPins[rows] = {5, 6, 7, 8};
byte colPins[cols] = {9, 10, 11, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

#define roomDht DHT22
#define ambDht DHT11
DHT roomDHT(roomTemp, roomDht);
DHT ambDHT(ambTemp, ambDht);

Servo myServo;

#define _maxOpen 0
#define _open1 30
#define _open2 60
#define _open3 90
#define _open4 120
#define _open5 150
#define _close 180

float ambT = 0.0;
float initialRoomT = 0.0;
float currentRoomT = 0.0;
float error = 0.0;
int angle = 0.0;
bool controlType = 0.0;
bool _isManDone = false;

double currentTime = 0.0;

void welcome();
bool initialization();
void autoControl();
void manualControl();
void updateLCD();

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  roomDHT.begin();
  ambDHT.begin();

  myServo.attach(servoPin);

  welcome();
  initialRoomT = roomDHT.readTemperature();
  controlType = initialization();

  currentTime = millis();
}

void loop() {
  if (controlType)
    autoControl();
  else {
    ambT = ambDHT.readTemperature();
    currentRoomT = roomDHT.readTemperature();
    error = initialRoomT - currentRoomT;
    if (!_isManDone) {
      manualControl();
    }
  }
  delay(2000);
  if (millis() - currentTime >= 8.0e+3 || currentTime < 500.0) {
    updateLCD();
    currentTime = millis();
  }
  myServo.write(angle);
  Serial.println(angle);
}

void welcome() {
  char line1[] = "Temperature Controlled";
  char line2[] = "->Smart Window<-";
  lcd.setCursor(16, 0);
  lcd.autoscroll();

  for (int i = 0; i < strlen(line1) + 16; i++) {
    if (i < strlen(line1)) {
      lcd.print(line1[i]);
    }
    else {
      lcd.print(" ");
    }

    delay(150);
  }
  lcd.noAutoscroll();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(line2);
  delay(3000);
  lcd.clear();
  myServo.write(_close);
}

bool initialization() {
  lcd.setCursor(0, 0);
  lcd.print("Your Choice:-");
  lcd.setCursor(0, 1);
  lcd.print("A:Auto");
  lcd.setCursor(11, 1);
  lcd.print("B:Man");

  char key = keypad.getKey();
  while (key == NO_KEY)
    key = keypad.getKey();
  if (key == 'A') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Auto Control");
    delay(2000);
    return true;
  }
  else if (key == 'B') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Manual Control");
    delay(2000);
    return false;
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid Input");
    delay(2000);
    initialization();
  }
  return true;
}

void autoControl() {
  ambT = ambDHT.readTemperature();
  ambT=40;
  currentRoomT = roomDHT.readTemperature();

  if (currentRoomT > ambT) {
    Serial.println("Winter");
    error = initialRoomT - currentRoomT;
    if (error >= 10)
      angle = _maxOpen;
    else if (error < 10 && error >= 8)
      angle = _open1;
    else if (error < 8 && error >= 6)
      angle = _open2;
    else if (error < 6 && error >= 4)
      angle = _open3;
    else if (error < 4 && error >= 2)
      angle = _open4;
    else if (error < 2 && error >= 1)
      angle = _open5;
    else if (error < 1)
      angle = _close;
  }

  if (currentRoomT < ambT) {
     Serial.println("Summer");
    error = initialRoomT - currentRoomT;
    if (error >= 10)
      angle = _close;
    else if (error < 10 && error >= 8)
      angle = _open5;
    else if (error < 8 && error >= 6)
      angle = _open4;
    else if (error < 6 && error >= 4)
      angle = _open3;
    else if (error < 4 && error >= 2)
      angle = _open2;
    else if (error < 2 && error >= 1)
      angle = _open1;
    else if (error < 1)
      angle = _maxOpen;
  }
}

void manualControl() {
  char myInput[3] = {'n', 'n', 'n'};
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Angle:-");
  for (int i = 0; i < 3; i++)
  {
    char key = keypad.getKey();
    while (key == NO_KEY)
      key = keypad.getKey();
    if ((key < 48 || key > 57) && !(key == 68)) {
      i--;
      continue;
    }
    else if (key == 68)
      break;
    myInput[i] = key;
    lcd.setCursor(i, 1);
    lcd.print(key);
  }
  lcd.clear();
  int mul = 1;

  for (int i = 2; i >= 0; i--) {
    if (myInput[i] != 'n') {
      angle = angle + (myInput[i] - 48) * mul;
      mul = mul * 10;
    }
  }
  Serial.println(angle);

  if (angle > _close)
    angle = _close;
  else if (angle < _maxOpen)
    angle = _maxOpen;
  Serial.println(angle);
  _isManDone = true;
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ins Temp: " + String(currentRoomT));
  lcd.setCursor(0, 1);
  lcd.print("Set Temp: " + String(initialRoomT));
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Error: " + String(error));
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Angle: " + String(angle));
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Amb Temp: " + String(ambT));
  delay(1500);
  lcd.setCursor(0, 1);
  lcd.print("                ");
}
